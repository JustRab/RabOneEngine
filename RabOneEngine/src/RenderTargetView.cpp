#include "RenderTargetView.h"
#include "Device.h"
#include "DeviceContext.h"
#include "Texture.h"
#include "DepthStencilView.h"

HRESULT 
RenderTargetView::init(Device& device,
                      Texture& backBuffer,
                      DXGI_FORMAT format)
{
  if (!device.m_device) {
    ERROR("RenderTargetView", "init", "Invalid device. (m_device is nullptr)");
    return E_POINTER;
  }
  if (!backBuffer.m_texture) {
    ERROR("RenderTargetView", "init", "Invalid texture. (m_texture is nullptr)");
    return E_POINTER;
  }
  if (format == DXGI_FORMAT_UNKNOWN)
  {
    ERROR("RenderTargetView", "init", "Format is DXGI_FORMAT_UNKNOWN.");
    return E_INVALIDARG;
  }

  // Config the description for the render target view
  D3D11_RENDER_TARGET_VIEW_DESC desc;
  memset(&desc, 0, sizeof(desc));
  desc.Format = format;
  desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DMS;

  // Create the render target view
  HRESULT hr = device.CreateRenderTargetView(backBuffer.m_texture, &desc, &m_renderTargetView);

  if (FAILED(hr)) {
    ERROR("RenderTargetView", "init", ("Failed to create render target view. HRESULT: " + std::to_string(hr)).c_str());
    return hr;
  }
  return S_OK;
}

HRESULT 
RenderTargetView::init(Device& device,
                      Texture& inTex,
                      D3D11_RTV_DIMENSION viewDimension,
                      DXGI_FORMAT format)
{
  if (!device.m_device) {
    ERROR("RenderTargetView", "init", "Invalid device. (m_device is nullptr)");
    return E_POINTER;
  }
  if (!inTex.m_texture) {
    ERROR("RenderTargetView", "init", "Invalid texture. (m_texture is nullptr)");
    return E_POINTER;
  }
  /*if (viewDimension != D3D11_RTV_DIMENSION_TEXTURE2D &&
    viewDimension != D3D11_RTV_DIMENSION_TEXTURE2DARRAY &&
    viewDimension != D3D11_RTV_DIMENSION_TEXTURE2DMS &&
    viewDimension != D3D11_RTV_DIMENSION_TEXTURE2DMSARRAY &&
    viewDimension != D3D11_RTV_DIMENSION_TEXTURE3D)
  {
    ERROR("RenderTargetView", "init", "Invalid view dimension.");
    return E_INVALIDARG;
  } Esto es solo util en casos de Skybox a palabras del profesor. */
  if (format == DXGI_FORMAT_UNKNOWN)
  {
    ERROR("RenderTargetView", "init", "Format is DXGI_FORMAT_UNKNOWN.");
    return E_INVALIDARG;
  }

  // Config the description for the render target view
  D3D11_RENDER_TARGET_VIEW_DESC desc;
  memset(&desc, 0, sizeof(desc));
  desc.Format = format;
  desc.ViewDimension = viewDimension;

  // Create the render target view
  HRESULT hr = device.CreateRenderTargetView(inTex.m_texture, &desc, &m_renderTargetView);
  if (FAILED(hr)) {
    ERROR("RenderTargetView", "init", ("Failed to create render target view. HRESULT: " + std::to_string(hr)).c_str());
    return hr;
  }

  return S_OK;
}

void 
RenderTargetView::render(DeviceContext& deviceContext,
                        DepthStencilView& depthStencilView,
                        unsigned int numViews,
                        const float ClearColor[4])
{
  if (!deviceContext.m_deviceContext) {
    ERROR("RenderTargetView", "render", "Invalid device context. (m_deviceContext is nullptr)");
    return;
  }
  if (!m_renderTargetView) {
    ERROR("RenderTargetView", "render", "Invalid render target view. (m_renderTargetView is nullptr)");
    return;
  }
  if (!depthStencilView.m_depthStencilView) {
    ERROR("RenderTargetView", "render", "Invalid depth stencil view. (m_depthStencilView is nullptr)");
    return;
  }

  // Clear the render target view
  deviceContext.m_deviceContext->ClearRenderTargetView(m_renderTargetView, ClearColor);

  // Config render target view & depth stencil view
  deviceContext.m_deviceContext->OMSetRenderTargets(numViews, &m_renderTargetView, depthStencilView.m_depthStencilView);
}

void 
RenderTargetView::render(DeviceContext& deviceContext,
                        unsigned int numViews)
{
  if (!deviceContext.m_deviceContext) {
    ERROR("RenderTargetView", "render", "Invalid device context. (m_deviceContext is nullptr)");
    return;
  }
  if (!m_renderTargetView) {
    ERROR("RenderTargetView", "render", "Invalid render target view. (m_renderTargetView is nullptr)");
    return;
  }
  // Config render target view
  deviceContext.m_deviceContext->OMSetRenderTargets(numViews, &m_renderTargetView, nullptr);
}


void 
RenderTargetView::destroy()
{
  SAFE_RELEASE(m_renderTargetView);
}