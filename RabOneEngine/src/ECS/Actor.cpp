#include "ECS/Actor.h"
#include "MeshComponent.h"
#include "Device.h"
#include "DeviceContext.h"

Actor::Actor(Device& device) {
  // Setup Default Components
  EngineUtilities::TSharedPointer<MeshComponent> meshComponent = EngineUtilities::MakeShared<MeshComponent>();
  addComponent(meshComponent);

  HRESULT hr;
  std::string classNameType = "Actor -> " + m_name;
  hr = m_modelBuffer.init(device, sizeof(CBChangesEveryFrame));
  if (FAILED(hr)) {
    ERROR("Actor", classNameType.c_str(), "Failed to create new CBChangesEveryFrame");
  }
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
  //m_model.mWorld = XMMatrixTranspose(getComponent<Transform>()->m_matrix);
  m_model.vMeshColor = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f); // Default color

  // Update the constant buffer
  m_modelBuffer.update(deviceContext, nullptr, 0, nullptr, &m_model, 0, 0);
}

void
Actor::render(DeviceContext& deviceContext) {
  // Render Rasterizer, Sampler and Blendstate oner per time updating the mesh
  // m_rasterizer.render(deviceContext);
  // m_blendState.render(deviceContext);
  // m_sampler.render(deviceContext, 0, 1);

  // Update buffer and render all components
  for (unsigned int i = 0; i < m_components.size(); ++i) {
    m_vertexBuffers[i].render(deviceContext, 0, 1);
    m_indexBuffers[i].render(deviceContext, 0, 1, false, DXGI_FORMAT_R32_UINT);

    // Render mesh texure
    if (m_textures.size() > 0) {
      if (i < m_textures.size()) {
        m_textures[i].render(deviceContext, 0, 1);
      }
    }

    m_modelBuffer.render(deviceContext, 2, 1, true);

    deviceContext.m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    deviceContext.m_deviceContext->DrawIndexed(m_meshes[i].m_numIndex, 0, 0);
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

  for (auto& texture : m_textures) {
    texture.destroy();
  }
  m_modelBuffer.destroy();

  //m_rasterizer.destroy();
  //m_blendState.destroy();
  //m_sampler.destroy();
}

void
Actor::SetMesh(Device& device, std::vector<MeshComponent> meshes) {
  m_meshes = meshes;
  HRESULT hr;
  for (const auto& mesh : m_meshes) {
    // Create vertex buffer
    Buffer vertexBuffer;
    hr = vertexBuffer.init(device, mesh, D3D11_BIND_VERTEX_BUFFER);
    if (FAILED(hr)) {
      ERROR("Actor", "SetMesh", ("Failed to initialize VertexBuffer for mesh: " + mesh.m_name).c_str());
    }
    else {
      m_vertexBuffers.push_back(vertexBuffer);
    }

    // Create index buffer
    Buffer indexBuffer;
    hr = indexBuffer.init(device, mesh, D3D11_BIND_INDEX_BUFFER);
    if (FAILED(hr)) {
      ERROR("Actor", "SetMesh", ("Failed to initialize IndexBuffer for mesh: " + mesh.m_name).c_str());
    }
    else {
      m_indexBuffers.push_back(indexBuffer);
    }
  }
}