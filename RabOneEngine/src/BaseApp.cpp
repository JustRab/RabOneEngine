#include "BaseApp.h"

XMFLOAT4                            g_LightPos(2.0f, 4.0f, -2.0f, 1.0f); // Posición de la luz
XMFLOAT4                            g_vMeshColor(0.7f, 0.7f, 0.7f, 1.0f);

// Inicializa
HRESULT
BaseApp::init() {
  HRESULT hr = S_OK;

  hr = g_swapChain.init(g_device, g_deviceContext, g_backBuffer, g_window);

  if (FAILED(hr)) {
    ERROR("Main", "InitDevice", ("Failed to initialize swap chain. HRESULT: " + std::to_string(hr)).c_str());
    return hr;
  }

  hr = g_renderTargetView.init(g_device, g_backBuffer, DXGI_FORMAT_R8G8B8A8_UNORM);
  if (FAILED(hr)) {
    ERROR("Main", "InitDevice", ("Failed to initialize render target view. HRESULT: " + std::to_string(hr)).c_str());
    return hr;
  }

  // Crear textura de depth stencil
  hr = g_depthStencil.init(g_device, g_window.m_width, g_window.m_height,
    DXGI_FORMAT_D24_UNORM_S8_UINT, D3D11_BIND_DEPTH_STENCIL, 4, 0);

  if (FAILED(hr)) {
    ERROR("Main", "InitDevice", ("Failed to initialize depth stencil texture. HRESULT: " + std::to_string(hr)).c_str());
    return hr;
  }

  // Crear el depth stencil view
  hr = g_depthStencilView.init(g_device,
    g_depthStencil, DXGI_FORMAT_D24_UNORM_S8_UINT);

  if (FAILED(hr)) {
    ERROR("Main", "InitDevice", ("Failed to initialize depth stencil view. HRESULT: " + std::to_string(hr)).c_str());
    return hr;
  }

  // g_deviceContext.m_deviceContext->OMSetRenderTargets(1, &g_renderTargetView, g_pDepthStencilView);

      // Crear el g_viewport
  hr = g_viewport.init(g_window);

  if (FAILED(hr)) {
    ERROR("Main", "InitDevice",
      ("Failed to initialize Viewport. HRESULT: " + std::to_string(hr)).c_str());
    return hr;
  }

  // Definir el layout de entrada
  std::vector<D3D11_INPUT_ELEMENT_DESC> Layout;

  D3D11_INPUT_ELEMENT_DESC position;
  position.SemanticName = "POSITION";
  position.SemanticIndex = 0;
  position.Format = DXGI_FORMAT_R32G32B32_FLOAT;
  position.InputSlot = 0;
  position.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT /*0*/;
  position.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
  position.InstanceDataStepRate = 0;
  Layout.push_back(position);

  D3D11_INPUT_ELEMENT_DESC texcoord;
  texcoord.SemanticName = "TEXCOORD";
  texcoord.SemanticIndex = 0;
  texcoord.Format = DXGI_FORMAT_R32G32_FLOAT;
  texcoord.InputSlot = 0;
  texcoord.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT /*12*/;
  texcoord.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
  texcoord.InstanceDataStepRate = 0;
  Layout.push_back(texcoord);

  // Create the Shader Program
  hr = g_shaderProgram.init(g_device, "RabOneEngine.fx", Layout);

  if (FAILED(hr)) {
    ERROR("Main", "InitDevice",
      ("Failed to initialize ShaderProgram. HRESULT: " + std::to_string(hr)).c_str());
    return hr;
  }

  // Load Model
  LoadData LD = m_loader.Load("models/koroGod.obj");

  // Usar los datos del modelo en vez del cubo
  cubeMesh.m_vertex = LD.vertex;
  cubeMesh.m_index = LD.index;

  // Ya no necesitas definir los vértices/índices del cubo manualmente

  hr = m_vertexBuffer.init(g_device, cubeMesh, D3D11_BIND_VERTEX_BUFFER);
  if (FAILED(hr)) {
    ERROR("Main", "InitDevice",
      ("Failed to initialize VertexBuffer. HRESULT: " + std::to_string(hr)).c_str());
    return hr;
  }

  hr = m_indexBuffer.init(g_device, cubeMesh, D3D11_BIND_INDEX_BUFFER);
  if (FAILED(hr)) {
    ERROR("Main", "InitDevice",
      ("Failed to initialize IndexBuffer. HRESULT: " + std::to_string(hr)).c_str());
    return hr;
  }

  /*// Crear vertex buffer y index buffer para el cubo
  SimpleVertex vertices[] = {
      { XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT2(0.0f, 0.0f) },
      { XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
      { XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f) },
      { XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },

      { XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT2(0.0f, 0.0f) },
      { XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
      { XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f) },
      { XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },

      { XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f) },
      { XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
      { XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT2(1.0f, 1.0f) },
      { XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },

      { XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f) },
      { XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
      { XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT2(1.0f, 1.0f) },
      { XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },

      { XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT2(0.0f, 0.0f) },
      { XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
      { XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT2(1.0f, 1.0f) },
      { XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT2(0.0f, 1.0f) },

      { XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f) },
      { XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT2(1.0f, 0.0f) },
      { XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f) },
      { XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },
  };
  unsigned int indices[] = {
      3,1,0,
      2,1,3,

      6,4,5,
      7,4,6,

      11,9,8,
      10,9,11,

      14,12,13,
      15,12,14,

      19,17,16,
      18,17,19,

      22,20,21,
      23,20,22
  };

  // Store the vertex data
  for (int i = 0; i < 24; i++) {
    cubeMesh.m_vertex.push_back(vertices[i]);
  }
  // Store the index data
  for (int i = 0; i < 36; i++) {
    cubeMesh.m_index.push_back(indices[i]);
  }

  hr = m_vertexBuffer.init(g_device, cubeMesh, D3D11_BIND_VERTEX_BUFFER);

  if (FAILED(hr)) {
    ERROR("Main", "InitDevice",
      ("Failed to initialize VertexBuffer. HRESULT: " + std::to_string(hr)).c_str());
    return hr;
  }

  hr = m_indexBuffer.init(g_device, cubeMesh, D3D11_BIND_INDEX_BUFFER);

  if (FAILED(hr)) {
    ERROR("Main", "InitDevice",
      ("Failed to initialize IndexBuffer. HRESULT: " + std::to_string(hr)).c_str());
    return hr;
  }*/

  // Establecer topología primitiva
  g_deviceContext.m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

  // Crear los constant buffers
  hr = m_neverChanges.init(g_device, sizeof(CBNeverChanges));
  if (FAILED(hr)) {
    ERROR("Main", "InitDevice",
      ("Failed to initialize NeverChanges Buffer. HRESULT: " + std::to_string(hr)).c_str());
    return hr;
  }

  hr = m_changeOnResize.init(g_device, sizeof(CBChangeOnResize));
  if (FAILED(hr)) {
    ERROR("Main", "InitDevice",
      ("Failed to initialize ChangeOnResize Buffer. HRESULT: " + std::to_string(hr)).c_str());
    return hr;
  }

  hr = m_changeEveryFrame.init(g_device, sizeof(CBChangesEveryFrame));
  if (FAILED(hr)) {
    ERROR("Main", "InitDevice",
      ("Failed to initialize ChangesEveryFrame Buffer. HRESULT: " + std::to_string(hr)).c_str());
    return hr;
  }

  // Cargar la textura del modelo
  hr = D3DX11CreateShaderResourceViewFromFile(g_device.m_device, "textures/korotexture.png", NULL, NULL, &g_pTextureRV, NULL);
  if (FAILED(hr))
    return hr;

  // Cargar la textura del plano
  hr = D3DX11CreateShaderResourceViewFromFile(g_device.m_device, "seafloor.dds", NULL, NULL, &g_pPlaneTextureRV, NULL);
  if (FAILED(hr))
    return hr;

  // Crear el sampler state para ambos
  D3D11_SAMPLER_DESC sampDesc;
  ZeroMemory(&sampDesc, sizeof(sampDesc));
  sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
  sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
  sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
  sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
  sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
  sampDesc.MinLOD = 0;
  sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
  hr = g_device.m_device->CreateSamplerState(&sampDesc, &g_pSamplerLinear);
  if (FAILED(hr))
    return hr;
  hr = g_device.m_device->CreateSamplerState(&sampDesc, &g_pPlaneSamplerLinear);
  if (FAILED(hr))
    return hr;

  // Inicializar las matrices de mundo, vista y proyección
  XMVECTOR Eye = XMVectorSet(0.0f, 3.0f, -6.0f, 0.0f);
  XMVECTOR At = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
  XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
  g_View = XMMatrixLookAtLH(Eye, At, Up);

  // Actualizar la matriz de proyección
  cbNeverChanges.mView = XMMatrixTranspose(g_View);
  g_Projection = XMMatrixPerspectiveFovLH(XM_PIDIV4, g_window.m_width / (FLOAT)g_window.m_height, 0.01f, 100.0f);
  cbChangesOnResize.mProjection = XMMatrixTranspose(g_Projection);

  //------- CREACIÓN DE GEOMETRÍA DEL PLANO (suelo) -------//
  SimpleVertex planeVertices[] =
  {
      { XMFLOAT3(-20.0f, 0.0f, -20.0f), XMFLOAT2(0.0f, 0.0f) },
      { XMFLOAT3(20.0f, 0.0f, -20.0f), XMFLOAT2(1.0f, 0.0f) },
      { XMFLOAT3(20.0f, 0.0f,  20.0f), XMFLOAT2(1.0f, 1.0f) },
      { XMFLOAT3(-20.0f, 0.0f,  20.0f), XMFLOAT2(0.0f, 1.0f) },
  };

  WORD planeIndices[] =
  {
      0, 2, 1,
      0, 3, 2
  };

  g_planeIndexCount = 6;

  // Store the vertex data
  for (int i = 0; i < 4; i++) {
    planeMesh.m_vertex.push_back(planeVertices[i]);
  }
  // Store the index data
  for (int i = 0; i < 6; i++) {
    planeMesh.m_index.push_back(planeIndices[i]);
  }

  // Crear el vertex buffer y index buffer para el plano
  hr = m_planeVertexBuffer.init(g_device, planeMesh, D3D11_BIND_VERTEX_BUFFER);

  if (FAILED(hr)) {
    ERROR("Main", "InitDevice",
      ("Failed to initialize PlaneVertexBuffer. HRESULT: " + std::to_string(hr)).c_str());
    return hr;
  }

  hr = m_planeIndexBuffer.init(g_device, planeMesh, D3D11_BIND_INDEX_BUFFER);

  if (FAILED(hr)) {
    ERROR("Main", "InitDevice",
      ("Failed to initialize PlaneIndexBuffer. HRESULT: " + std::to_string(hr)).c_str());
    return hr;
  }

  hr = m_constPlane.init(g_device, sizeof(CBChangesEveryFrame));
  if (FAILED(hr)) {
    ERROR("Main", "InitDevice",
      ("Failed to initialize Plane Buffer. HRESULT: " + std::to_string(hr)).c_str());
    return hr;
  }

  //------- COMPILAR SHADER DE SOMBRA -------//
  hr = g_shaderShadow.CreateShader(g_device, PIXEL_SHADER, "RabOneEngine.fx");

  if (FAILED(hr)) {
    ERROR("Main", "InitDevice",
      ("Failed to initialize Shadow Shader. HRESULT: " + std::to_string(hr)).c_str());
    return hr;
  }

  hr = m_constShadow.init(g_device, sizeof(CBChangesEveryFrame));
  if (FAILED(hr)) {
    ERROR("Main", "InitDevice",
      ("Failed to initialize Shadow Buffer. HRESULT: " + std::to_string(hr)).c_str());
    return hr;
  }

  //------- CREAR ESTADOS DE BLENDING Y DEPTH STENCIL PARA LAS SOMBRAS -------//
  hr = g_shadowBlendState.init(g_device);
  if (FAILED(hr)) {
    ERROR("Main", "InitDevice",
      ("Failed to initialize Shadow Blend State. HRESULT: " + std::to_string(hr)).c_str());
    return hr;
  }

  hr = g_shadowDepthStencilState.init(g_device, true, false);

  if (FAILED(hr)) {
    ERROR("Main", "InitDevice",
      ("Failed to initialize Depth Stencil State. HRESULT: " + std::to_string(hr)).c_str());
    return hr;
  }

  // Initialize the world matrices
  scale.x = 1.0f;
  scale.y = 1.0f;
  scale.z = 1.0f;
  
  g_userInterface.init(g_window.m_hWnd, g_device.m_device, g_deviceContext.m_deviceContext);

  return S_OK;
}

// Actualiza el estado de la aplicación. Debe ser sobreescrito por clases derivadas.
void
BaseApp::update() {
  // Actualizar la interfaz de usuario
  g_userInterface.update();

  g_userInterface.GUITab("RabOne Main");
  g_userInterface.TransformGUI(*this);

  // Actualizar tiempo (mismo que antes)
  static float t = 0.0f;
  if (g_swapChain.m_driverType == D3D_DRIVER_TYPE_REFERENCE)
  {
    t += (float)XM_PI * 0.0125f;
  }
  else
  {
    static DWORD dwTimeStart = 0;
    DWORD dwTimeCur = GetTickCount();
    if (dwTimeStart == 0)
      dwTimeStart = dwTimeCur;
    t = (dwTimeCur - dwTimeStart) / 1000.0f;
  }

  // Actualizar la matriz de proyección y vista
  cbNeverChanges.mView = XMMatrixTranspose(g_View);
  m_neverChanges.update(g_deviceContext, nullptr, 0, nullptr, &cbNeverChanges, 0, 0);
  cbChangesOnResize.mProjection = XMMatrixTranspose(g_Projection);
  m_changeOnResize.update(g_deviceContext, nullptr, 0, nullptr, &cbChangesOnResize, 0, 0);

  // --- Transformación del cubo ---
  // Parámetros del cubo:
  float cubePosX = position.x, cubePosY = position.y, cubePosZ = position.z;  // Ubicado 2 unidades arriba
  //float cubeScale = 1.0f;                                    // Escala uniforme
  float cubeAngleX = rotation.x, cubeAngleY = rotation.y, cubeAngleZ = rotation.z;  // Rotación dinámica en Y

  // Crear las matrices individuales
  XMMATRIX cubeScaleMat = XMMatrixScaling(scale.x, scale.y, scale.z);
  XMMATRIX cubeRotMat = XMMatrixRotationX(cubeAngleX) *
    XMMatrixRotationY(cubeAngleY) *
    XMMatrixRotationZ(cubeAngleZ);
  XMMATRIX cubeTransMat = XMMatrixTranslation(cubePosX, cubePosY, cubePosZ);

  // Combinar: primero escala, luego rota y por último traslada
  g_World = cubeTransMat * cubeRotMat * cubeScaleMat;

  // Actualizar el color animado del cubo
  g_vMeshColor.x = (sinf(t * 1.0f) + 1.0f) * 0.5f;
  g_vMeshColor.y = (cosf(t * 3.0f) + 1.0f) * 0.5f;
  g_vMeshColor.z = (sinf(t * 5.0f) + 1.0f) * 0.5f;

  // --- Transformación del plano ---
  // Parámetros para el plano:
  float planePosX = 0.0f, planePosY = -5.0f, planePosZ = 0.0f;
  // Aunque los vértices ya definen un plano extenso (-20 a 20), aquí puedes ajustar el escalado adicional
  float planeScaleFactor = 1.0f; // Puedes modificar este factor para agrandar o reducir el plano
  float planeAngleX = 0.0f, planeAngleY = 0.0f, planeAngleZ = 0.0f; // Sin rotación por defecto

  XMMATRIX planeScaleMat = XMMatrixScaling(planeScaleFactor, planeScaleFactor, planeScaleFactor);
  XMMATRIX planeRotMat = XMMatrixRotationX(planeAngleX) *
    XMMatrixRotationY(planeAngleY) *
    XMMatrixRotationZ(planeAngleZ);
  XMMATRIX planeTransMat = XMMatrixTranslation(planePosX, planePosY, planePosZ);

  // Combinar transformaciones para el plano
  g_PlaneWorld = planeTransMat * planeRotMat * planeScaleMat;

  // Update Plane
  cbPlane.mWorld = XMMatrixTranspose(g_PlaneWorld);
  cbPlane.vMeshColor = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
  m_constPlane.update(g_deviceContext, nullptr, 0, nullptr, &cbPlane, 0, 0);

  // Update cube
  cb.mWorld = XMMatrixTranspose(g_World);
  cb.vMeshColor = g_vMeshColor;
  m_changeEveryFrame.update(g_deviceContext, nullptr, 0, nullptr, &cb, 0, 0);

  // Update Shadow cube
  float dot = g_LightPos.y;
  XMMATRIX shadowMatrix = XMMATRIX(
    dot, -g_LightPos.x, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, -g_LightPos.z, dot, 0.0f,
    0.0f, -1.0f, 0.0f, dot
  );
  XMMATRIX shadowWorld = g_World * shadowMatrix;
  cbShadow.mWorld = XMMatrixTranspose(shadowWorld);
  cbShadow.vMeshColor = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.5f);
  m_constShadow.update(g_deviceContext, nullptr, 0, nullptr, &cbShadow, 0, 0);
}

// Renderiza la escena o interfaz de la aplicación.
void
BaseApp::render() {
  // Limpiar el back buffer y el depth buffer
  float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f };
  g_renderTargetView.render(g_deviceContext, g_depthStencilView, 1, ClearColor);

  // Set Viewport
  g_viewport.render(g_deviceContext);

  g_depthStencilView.render(g_deviceContext);

  // Configurar los buffers y shaders para el pipeline
  g_shaderProgram.render(g_deviceContext);

  // Asignar buffers constantes
  m_neverChanges.render(g_deviceContext, 0, 1);
  m_changeOnResize.render(g_deviceContext, 1, 1);

  //------------- Renderizar el plano (suelo) -------------//
  m_planeVertexBuffer.render(g_deviceContext, 0, 1);
  m_planeIndexBuffer.render(g_deviceContext, 0, 1, false, DXGI_FORMAT_R32_UINT);
  m_constPlane.render(g_deviceContext, 2, 1);
  m_constPlane.render(g_deviceContext, 2, 1, true);
  // Usa la textura y sampler del plano
  g_deviceContext.m_deviceContext->PSSetShaderResources(0, 1, &g_pPlaneTextureRV);
  g_deviceContext.m_deviceContext->PSSetSamplers(0, 1, &g_pPlaneSamplerLinear);
  g_deviceContext.m_deviceContext->DrawIndexed(planeMesh.m_index.size(), 0, 0);

  //------------- Renderizar el modelo -------------//
  m_vertexBuffer.render(g_deviceContext, 0, 1);
  m_indexBuffer.render(g_deviceContext, 0, 1, false, DXGI_FORMAT_R32_UINT);
  m_changeEveryFrame.render(g_deviceContext, 2, 1);
  m_changeEveryFrame.render(g_deviceContext, 2, 1, true);
  // Usa la textura y sampler del modelo
  g_deviceContext.m_deviceContext->PSSetShaderResources(0, 1, &g_pTextureRV);
  g_deviceContext.m_deviceContext->PSSetSamplers(0, 1, &g_pSamplerLinear);
  g_deviceContext.m_deviceContext->DrawIndexed(cubeMesh.m_index.size(), 0, 0);


  //------------- Renderizar el cubo (normal) -------------//
  // Asignar buffers Vertex e Index
  m_vertexBuffer.render(g_deviceContext, 0, 1);

  m_indexBuffer.render(g_deviceContext, 0, 1, false, DXGI_FORMAT_R32_UINT);

  // Asignar buffers constantes
  m_changeEveryFrame.render(g_deviceContext, 2, 1);
  m_changeEveryFrame.render(g_deviceContext, 2, 1, true);

  g_deviceContext.m_deviceContext->PSSetShaderResources(0, 1, &g_pTextureRV);
  g_deviceContext.m_deviceContext->PSSetSamplers(0, 1, &g_pSamplerLinear);
  g_deviceContext.m_deviceContext->DrawIndexed(cubeMesh.m_index.size(), 0, 0);

  //------------- Renderizar la sombra del cubo -------------//
  g_shaderShadow.render(g_deviceContext, PIXEL_SHADER);

  g_shadowBlendState.render(g_deviceContext, blendFactor, 0xffffffff);
  g_shadowDepthStencilState.render(g_deviceContext, 0);

  // Asignar buffers Vertex e Index
  m_vertexBuffer.render(g_deviceContext, 0, 1);
  m_indexBuffer.render(g_deviceContext, 0, 1, false, DXGI_FORMAT_R32_UINT);

  // Asignar buffers constantes
  m_constShadow.render(g_deviceContext, 2, 1, true);

  g_deviceContext.m_deviceContext->DrawIndexed(cubeMesh.m_index.size(), 0, 0);

  g_shadowBlendState.render(g_deviceContext, blendFactor, 0xffffffff, true);
  g_shadowDepthStencilState.render(g_deviceContext, 0, true);

  g_userInterface.render();

  // Presentar el back buffer al front buffer
  g_swapChain.present();
}

// Libera los recursos utilizados por la aplicación. 
void
BaseApp::destroy() {
  if (g_deviceContext.m_deviceContext) g_deviceContext.m_deviceContext->ClearState();

  g_shadowBlendState.destroy();
  g_shadowDepthStencilState.destroy();
  g_shaderShadow.destroy();
  m_planeVertexBuffer.destroy();
  m_planeIndexBuffer.destroy();
  if (g_pSamplerLinear) g_pSamplerLinear->Release();
  if (g_pTextureRV) g_pTextureRV->Release();
  m_neverChanges.destroy();
  m_changeOnResize.destroy();
  m_changeEveryFrame.destroy();
  m_constPlane.destroy();
  m_constShadow.destroy();
  m_vertexBuffer.destroy();
  m_indexBuffer.destroy();
  g_shaderProgram.destroy();
  g_depthStencil.destroy();
  g_depthStencilView.destroy();
  g_renderTargetView.destroy();
  g_swapChain.destroy();
  if (g_deviceContext.m_deviceContext) g_deviceContext.m_deviceContext->Release();
  if (g_device.m_device) g_device.m_device->Release();
  g_userInterface.destroy();
}

// Ejecuta la aplicación, configurando el entorno y el bucle principal.
int
BaseApp::run(HINSTANCE hInstance,
  HINSTANCE hPrevInstance,
  LPWSTR lpCmdLine,
  int nCmdShow,
  WNDPROC wndproc) {

  UNREFERENCED_PARAMETER(hPrevInstance);
  UNREFERENCED_PARAMETER(lpCmdLine);

  if (FAILED(g_window.init(hInstance, nCmdShow, wndproc)))
    return 0;

  if (FAILED(init())) {
    destroy();
    return 0;
  }

  // Main message loop
  MSG msg = { 0 };
  while (WM_QUIT != msg.message)
  {
    if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
    else {
      update();
      render();
    }
  }

  destroy();

  return (int)msg.wParam;
}

