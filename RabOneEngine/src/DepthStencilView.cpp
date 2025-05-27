#include "DepthStencilView.h"
#include "Device.h"
#include "DeviceContext.h"
#include "Texture.h"

HRESULT DepthStencilView::init(Device& device, Texture& depthStencil, DXGI_FORMAT format)
{
	if (!device.m_device) {
		ERROR("DepthStencilView", "init", "Device is not initialized / is null.");
		return E_FAIL;
	}
	if (!depthStencil.m_texture) {
		ERROR("DepthStencilView", "init", "Texture is not initialized / is null.");
		return E_FAIL;
	}

	// Config depth stencil view description
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory(&descDSV, sizeof(descDSV));
	descDSV.Format = format;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
	descDSV.Texture2D.MipSlice = 0;

	// Create the depth stencil view
	HRESULT hr = device.CreateDepthStencilView(depthStencil.m_texture, 
		&descDSV, &m_depthStencilView);

	if (FAILED(hr)) {
		ERROR("DepthStencilView", "init", 
			("Failed to create depth stencil view. HRESULT: " + std::to_string(hr)).c_str());
		return hr;
	}

	return S_OK;
}

void 
DepthStencilView::render(DeviceContext& deviceContext)
{
	if (!deviceContext.m_deviceContext) {
		ERROR("DepthStencilView", "render", "Device context is not initialized / is null.");
		return;
	}
	if (!m_depthStencilView) {
		ERROR("DepthStencilView", "render", "Depth stencil view is not initialized / is null.");
		return;
	}
	// Clear depth stencil view
	deviceContext.m_deviceContext->ClearDepthStencilView(m_depthStencilView,
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void DepthStencilView::destroy()
{
	SAFE_RELEASE(m_depthStencilView);
}
