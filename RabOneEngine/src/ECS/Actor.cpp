#include "ECS/Actor.h"
#include "MeshComponent.h"
#include "Device.h"
#include "DeviceContext.h"

Actor::Actor(Device& device) {
	// Setup Default Components
	EngineUtilities::TSharedPointer<Transform> transform = EngineUtilities::MakeShared<Transform>();
	addComponent(transform);
	EngineUtilities::TSharedPointer<MeshComponent> meshComponent = EngineUtilities::MakeShared<MeshComponent>();
	addComponent(meshComponent);

	HRESULT hr;
	std::string classNameType = "Actor -> " + m_name;
	hr = m_modelBuffer.init(device, sizeof(CBChangesEveryFrame));
	if (FAILED(hr)) {
		ERROR("Actor", classNameType.c_str(), "Failed to create new CBChangesEveryFrame");
	}

	hr = m_sampler.init(device);
	if (FAILED(hr)) {
		ERROR("Actor", classNameType.c_str(), "Failed to create new SamplerState");
	}

	hr = m_rasterizer.init(device);
	if (FAILED(hr)) {
		ERROR("Actor", classNameType.c_str(), "Failed to create new Rasterizer");
	}

	hr = m_blendstate.init(device);
	if (FAILED(hr)) {
		ERROR("Actor", classNameType.c_str(), "Failed to create new BlendState");
	}

	hr = m_shaderShadow.CreateShader(device, PIXEL_SHADER, "RabOneEngine.fx");

	if (FAILED(hr)) {
		ERROR("Main", "InitDevice",
			("Failed to initialize Shadow Shader. HRESULT: " + std::to_string(hr)).c_str());
	}

	hr = m_shaderBuffer.init(device, sizeof(CBChangesEveryFrame));
	if (FAILED(hr)) {
		ERROR("Main", "InitDevice",
			("Failed to initialize Shadow Buffer. HRESULT: " + std::to_string(hr)).c_str());

	}

	hr = m_shadowBlendState.init(device);
	if (FAILED(hr)) {
		ERROR("Main", "InitDevice",
			("Failed to initialize Shadow Blend State. HRESULT: " + std::to_string(hr)).c_str());

	}

	hr = m_shadowDepthStencilState.init(device, true, false);

	if (FAILED(hr)) {
		ERROR("Main", "InitDevice",
			("Failed to initialize Depth Stencil State. HRESULT: " + std::to_string(hr)).c_str());

	}

	m_LightPos = XMFLOAT4(2.0f, 4.0f, -2.0f, 1.0f);
}

void
Actor::update(float deltaTime, DeviceContext& deviceContext) {
	// Update all components
	for (auto& component : m_components) {
		if (component) {
			component->update(deltaTime);
		}
	}

	// Update the model buffer
	m_model.mWorld = XMMatrixTranspose(getComponent<Transform>()->matrix);
	m_model.vMeshColor = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

	// Update the constant buffer
	m_modelBuffer.update(deviceContext, nullptr, 0, nullptr, &m_model, 0, 0);
}

void
Actor::render(DeviceContext& deviceContext) {
	// 1) Proyectar sombra primero (sobre el suelo)
	if (canCastShadow()) {
		renderShadow(deviceContext);
	}

	// 2) Configure blend state for proper alpha handling
	float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	m_blendstate.render(deviceContext, blendFactor, 0xffffffff);
	m_rasterizer.render(deviceContext);
	m_sampler.render(deviceContext, 0, 1);

	deviceContext.IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	
	// Update buffer and render all components
	for (unsigned int i = 0; i < m_meshes.size(); i++) {
		m_vertexBuffers[i].render(deviceContext, 0, 1);
		m_indexBuffers[i].render(deviceContext, 0, 1, false, DXGI_FORMAT_R32_UINT);
		
		// Bind del CB normal (world + color)
		m_modelBuffer.render(deviceContext, 2, 1, true);

		// Render mesh texture - improved texture binding
		if (!m_textures.empty()) {
			// Use modulo to ensure we don't go out of bounds
			int textureIndex = i % m_textures.size();
			m_textures[textureIndex].render(deviceContext, 0, 1);
		}

		// Draw the mesh
		deviceContext.DrawIndexed(m_meshes[i].m_numIndex, 0, 0);
		
		MESSAGE("Actor", "render", 
			"Rendered mesh " << i << " with " << m_meshes[i].m_numIndex << " indices");
	}
}

void
Actor::destroy() {
	for (auto& vertexBuffer : m_vertexBuffers) {
		vertexBuffer.destroy();
	}

	for (auto& indexBuffer : m_indexBuffers) {
		indexBuffer.destroy();
	}

	for (auto& tex : m_textures) {
		tex.destroy();
	}
	m_modelBuffer.destroy();

	m_rasterizer.destroy();
	m_blendstate.destroy();
	m_sampler.destroy();
}

void
Actor::SetMesh(Device& device, std::vector<MeshComponent> meshes) {
	m_meshes = meshes;
	HRESULT hr;
	for (auto& mesh : m_meshes) {
		// Crear vertex buffer
		Buffer vertexBuffer;
		hr = vertexBuffer.init(device, mesh, D3D11_BIND_VERTEX_BUFFER);
		if (FAILED(hr)) {
			ERROR("Actor", "setMesh", "Failed to create new vertexBuffer");
		}
		else {
			m_vertexBuffers.push_back(vertexBuffer);
		}

		// Crear index buffer
		Buffer indexBuffer;
		hr = indexBuffer.init(device, mesh, D3D11_BIND_INDEX_BUFFER);
		if (FAILED(hr)) {
			ERROR("Actor", "setMesh", "Failed to create new indexBuffer");
		}
		else {
			m_indexBuffers.push_back(indexBuffer);
		}
	}
}

void
Actor::renderShadow(DeviceContext& deviceContext) {
	// --- 1) Descomp�n world en traslaci�n + yaw + escala ---
	auto t = getComponent<Transform>();
	auto pos = t->getPosition();   // Vector3
	auto yaw = t->getRotation().y; // s�lo yaw
	auto scl = t->getScale();      // Vector3

	XMMATRIX Mscale = XMMatrixScaling(scl.x, scl.y, scl.z);
	XMMATRIX Myaw = XMMatrixRotationY(yaw);
	XMMATRIX Mtrans = XMMatrixTranslation(pos.x, pos.y, pos.z);
	XMMATRIX worldYaw = Mscale * Myaw * Mtrans;

	// --- 2) Construye la matriz de proyecci�n de sombra ---
	//   para proyectar v' = v - (v.y / Ly) * L
	float Lx = m_LightPos.x;
	float Ly = m_LightPos.y;
	float Lz = m_LightPos.z;
	float invLy = 1.0f / Ly;

	XMMATRIX S = XMMATRIX(
		1.0f, -Lx * invLy, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, -Lz * invLy, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	// --- 3) Aplica worldYaw * S para obtener la sombra en el suelo ---
	XMMATRIX worldShadow = worldYaw * S;
	// 2) Preparar y actualizar constant buffer
	m_cbShadow.mWorld = XMMatrixTranspose(worldShadow);
	m_cbShadow.vMeshColor = XMFLOAT4(0, 0, 0, 0.5f);
	m_shaderBuffer.update(deviceContext, nullptr, 0, nullptr, &m_cbShadow, 0, 0);
	m_shaderBuffer.render(deviceContext, 2, 1, true);

	// 3) Bind de shader y estados
	float blendFactor[4] = { 0.f, 0.f, 0.f, 0.f };
	m_shaderShadow.render(deviceContext, PIXEL_SHADER);
	m_shadowBlendState.render(deviceContext, blendFactor, 0xffffffff);
	m_shadowDepthStencilState.render(deviceContext, 0);

	deviceContext.IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	// 4) Dibujar cada malla del actor
	for (size_t i = 0; i < m_meshes.size(); ++i) {
		m_vertexBuffers[i].render(deviceContext, 0, 1);
		m_indexBuffers[i].render(deviceContext, 0, 1, false, DXGI_FORMAT_R32_UINT);
		deviceContext.DrawIndexed(m_meshes[i].m_numIndex, 0, 0);
	}
}