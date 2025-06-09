#include "Device.h"

void
Device::destroy() {
  SAFE_RELEASE(m_device);
}

HRESULT
Device::CreateRenderTargetView(ID3D11Resource* pResource,
                               const D3D11_RENDER_TARGET_VIEW_DESC* pDesc,
                               ID3D11RenderTargetView** ppRTView) {
  // Validar parametros de entrada
  if (!pResource) {
    ERROR("Device", "CreateRenderTargetView", "pResource is nullptr");
    return E_INVALIDARG;
  }
  if (!ppRTView) {
    ERROR("Device", "CreateRenderTargetView", "ppRTView is nullptr");
    return E_POINTER;
  }

  // Crear el render target view
  HRESULT hr = m_device->CreateRenderTargetView(pResource, pDesc, ppRTView);

  if (SUCCEEDED(hr)) {
    MESSAGE("Device", "CreateRenderTargetView", "Render target view created successfully!");
  }
  else {
    ERROR("Device", "CreateRenderTargetView", ("Failed to create render target view. HRESULT: " + std::to_string(hr)).c_str());
  }
  return hr;
}

HRESULT
Device::CreateTexture2D(const D3D11_TEXTURE2D_DESC* pDesc,
                        const D3D11_SUBRESOURCE_DATA* pInitialData,
                        ID3D11Texture2D** ppTexture2D) {

  // Validar parametros de entrada
  if (!pDesc) {
    ERROR("Device", "CreateTexture2D", "pDesc is nullptr");
    return E_INVALIDARG;
  }
  if (!ppTexture2D) {
    ERROR("Device", "CreateTexture2D", "ppTexture2D is nullptr");
    return E_POINTER;
  }

  if (pDesc->Width == 0 || pDesc->Height == 0) {
    ERROR("Device", "CreateTexture2D", "Width or Height is zero");
    return E_INVALIDARG;
  }

  // Crear la textura 2D
  HRESULT hr = m_device->CreateTexture2D(pDesc, pInitialData, ppTexture2D);
  if (SUCCEEDED(hr)) {
    MESSAGE("Device", "CreateTexture2D", "Texture 2D created successfully!");
  }
  else {
    ERROR("Device", "CreateTexture2D", ("Failed to create texture 2D. HRESULT: " + std::to_string(hr)).c_str());
  }

  return hr;
}

HRESULT
Device::CreateDepthStencilView(ID3D11Resource* pResource,
  const D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc,
  ID3D11DepthStencilView** ppDepthStencilView) {

  // Validar parametros de entrada
  if (!pResource) {
    ERROR("Device", "CreateDepthStencilView", "pResource is nullptr");
    return E_INVALIDARG;
  }
  if (!ppDepthStencilView) {
    ERROR("Device", "CreateDepthStencilView", "ppDepthStencilView is nullptr");
    return E_POINTER;
  }

  // Crear el depth stencil view
  HRESULT hr = m_device->CreateDepthStencilView(pResource, pDesc, ppDepthStencilView);
  if (SUCCEEDED(hr)) {
    MESSAGE("Device", "CreateDepthStencilView", "Depth stencil view created successfully!");
  }
  else {
    ERROR("Device", "CreateDepthStencilView", ("Failed to create depth stencil view. HRESULT: " + std::to_string(hr)).c_str());
  }

  return hr;
}

HRESULT
Device::CreateVertexShader(const void* pShaderBytecode,
  SIZE_T BytecodeLength,
  ID3D11ClassLinkage* pClassLinkage,
  ID3D11VertexShader** ppVertexShader) {
  // Validar parametros de entrada
  if (!pShaderBytecode) {
    ERROR("Device", "CreateVertexShader", "pShaderBytecode is nullptr");
    return E_INVALIDARG;
  }
  if (!ppVertexShader) {
    ERROR("Device", "CreateVertexShader", "ppVertexShader is nullptr");
    return E_POINTER;
  }
  // Crear el vertex shader
  HRESULT hr = m_device->CreateVertexShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppVertexShader);
  if (SUCCEEDED(hr)) {
    MESSAGE("Device", "CreateVertexShader", "Vertex shader created successfully!");
  }
  else {
    ERROR("Device", "CreateVertexShader", ("Failed to create vertex shader. HRESULT: " + std::to_string(hr)).c_str());
  }
  return hr;
}

HRESULT
Device::CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* pInputElementDescs,
  UINT NumElements,
  const void* pShaderBytecodeWithInputSignature,
  SIZE_T BytecodeLength,
  ID3D11InputLayout** ppInputLayout) {
  // Validar parametros de entrada
  if (!pInputElementDescs) {
    ERROR("Device", "CreateInputLayout", "pInputElementDescs is nullptr");
    return E_INVALIDARG;
  }
  if (!ppInputLayout) {
    ERROR("Device", "CreateInputLayout", "ppInputLayout is nullptr");
    return E_POINTER;
  }
  // Crear el input layout
  HRESULT hr = m_device->CreateInputLayout(pInputElementDescs, NumElements, pShaderBytecodeWithInputSignature, BytecodeLength, ppInputLayout);
  if (SUCCEEDED(hr)) {
    MESSAGE("Device", "CreateInputLayout", "Input layout created successfully!");
  }
  else {
    ERROR("Device", "CreateInputLayout", ("Failed to create input layout. HRESULT: " + std::to_string(hr)).c_str());
  }
  return hr;
}

HRESULT
Device::CreatePixelShader(const void* pShaderBytecode,
  SIZE_T BytecodeLength,
  ID3D11ClassLinkage* pClassLinkage,
  ID3D11PixelShader** ppPixelShader) {
  // Validar parametros de entrada
  if (!pShaderBytecode) {
    ERROR("Device", "CreatePixelShader", "pShaderBytecode is nullptr");
    return E_INVALIDARG;
  }
  if (!ppPixelShader) {
    ERROR("Device", "CreatePixelShader", "ppPixelShader is nullptr");
    return E_POINTER;
  }
  // Crear el pixel shader
  HRESULT hr = m_device->CreatePixelShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppPixelShader);
  if (SUCCEEDED(hr)) {
    MESSAGE("Device", "CreatePixelShader", "Pixel shader created successfully!");
  }
  else {
    ERROR("Device", "CreatePixelShader", ("Failed to create pixel shader. HRESULT: " + std::to_string(hr)).c_str());
  }
  return hr;
}

HRESULT
Device::CreateSamplerState(const D3D11_SAMPLER_DESC* pSamplerDesc,
  ID3D11SamplerState** ppSamplerState) {
  // Validar parametros de entrada
  if (!pSamplerDesc) {
    ERROR("Device", "CreateSamplerState", "pSamplerDesc is nullptr");
    return E_INVALIDARG;
  }
  if (!ppSamplerState) {
    ERROR("Device", "CreateSamplerState", "ppSamplerState is nullptr");
    return E_POINTER;
  }
  // Crear el sampler state
  HRESULT hr = m_device->CreateSamplerState(pSamplerDesc, ppSamplerState);
  if (SUCCEEDED(hr)) {
    MESSAGE("Device", "CreateSamplerState", "Sampler state created successfully!");
  }
  else {
    ERROR("Device", "CreateSamplerState", ("Failed to create sampler state. HRESULT: " + std::to_string(hr)).c_str());
  }
  return hr;
}

HRESULT
Device::CreateBuffer(const D3D11_BUFFER_DESC* pDesc,
  const D3D11_SUBRESOURCE_DATA* pInitialData,
  ID3D11Buffer** ppBuffer) {
  // Validar parametros de entrada
  if (!pDesc) {
    ERROR("Device", "CreateBuffer", "pDesc is nullptr");
    return E_INVALIDARG;
  }
  if (!ppBuffer) {
    ERROR("Device", "CreateBuffer", "ppBuffer is nullptr");
    return E_POINTER;
  }
  // Crear el buffer
  HRESULT hr = m_device->CreateBuffer(pDesc, pInitialData, ppBuffer);
  if (SUCCEEDED(hr)) {
    MESSAGE("Device", "CreateBuffer", "Buffer created successfully!");
  }
  else {
    ERROR("Device", "CreateBuffer", ("Failed to create buffer. HRESULT: " + std::to_string(hr)).c_str());
  }
  return hr;
}

HRESULT
Device::CreateBlendState(const D3D11_BLEND_DESC* pBlendStateDesc,
  ID3D11BlendState** ppBlendState) {
  // Validar parametros de entrada
  if (!pBlendStateDesc) {
    ERROR("Device", "CreateBlendState", "pBlendStateDesc is nullptr");
    return E_INVALIDARG;
  }
  if (!ppBlendState) {
    ERROR("Device", "CreateBlendState", "ppBlendState is nullptr");
    return E_POINTER;
  }
  // Crear el blend state
  HRESULT hr = m_device->CreateBlendState(pBlendStateDesc, ppBlendState);
  if (SUCCEEDED(hr)) {
    MESSAGE("Device", "CreateBlendState", "Blend state created successfully!");
  }
  else {
    ERROR("Device", "CreateBlendState", ("Failed to create blend state. HRESULT: " + std::to_string(hr)).c_str());
  }
  return hr;
}

HRESULT
Device::CreateDepthStencilState(const D3D11_DEPTH_STENCIL_DESC* pDepthStencilDesc,
  ID3D11DepthStencilState** ppDepthStencilState) {
  // Validar parametros de entrada
  if (!pDepthStencilDesc) {
    ERROR("Device", "CreateDepthStencilState", "pDepthStencilDesc is nullptr");
    return E_INVALIDARG;
  }
  if (!ppDepthStencilState) {
    ERROR("Device", "CreateDepthStencilState", "ppDepthStencilState is nullptr");
    return E_POINTER;
  }
  // Crear el depth stencil state
  HRESULT hr = m_device->CreateDepthStencilState(pDepthStencilDesc, ppDepthStencilState);
  if (SUCCEEDED(hr)) {
    MESSAGE("Device", "CreateDepthStencilState", "Depth stencil state created successfully!");
  }
  else {
    ERROR("Device", "CreateDepthStencilState", ("Failed to create depth stencil state. HRESULT: " + std::to_string(hr)).c_str());
  }
  return hr;
}

HRESULT
Device::CreateRasterizerState(const D3D11_RASTERIZER_DESC* pRasterizerDesc,
  ID3D11RasterizerState** ppRasterizerState) {
  // Validar parametros de entrada
  if (!pRasterizerDesc) {
    ERROR("Device", "CreateRasterizerState", "pRasterizerDesc is nullptr");
    return E_INVALIDARG;
  }
  if (!ppRasterizerState) {
    ERROR("Device", "CreateRasterizerState", "ppRasterizerState is nullptr");
    return E_POINTER;
  }
  // Crear el rasterizer state
  HRESULT hr = m_device->CreateRasterizerState(pRasterizerDesc, ppRasterizerState);
  if (SUCCEEDED(hr)) {
    MESSAGE("Device", "CreateRasterizerState", "Rasterizer state created successfully!");
  }
  else {
    ERROR("Device", "CreateRasterizerState", ("Failed to create rasterizer state. HRESULT: " + std::to_string(hr)).c_str());
  }
  return hr;
}

