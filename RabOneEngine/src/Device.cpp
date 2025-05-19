#include "Device.h"

void Device::destroy(){
	SAFE_RELEASE(m_device);
}

HRESULT 
Device::CreateRenderTargetView(ID3D11Resource* pResource, 
								const D3D11_RENDER_TARGET_VIEW_DESC* pDesc, 
								ID3D11RenderTargetView** ppRTView){
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