#pragma once
#include "Prerequisites.h"

// Forward Declarations
class Device;
class DeviceContext;
class Texture;
class DepthStencilView;

class 
RenderTargetView
{
public:
	RenderTargetView() = default;
	~RenderTargetView() = default;

  // Initializes the render target view with a back buffer texture and specified format.
	HRESULT 
	init(Device& device, Texture &backBuffer, DXGI_FORMAT Format);

  // Initializes the render target view with a texture and specified view dimension and format.
	HRESULT
	init(Device& device, Texture& inTex, 
			D3D11_RTV_DIMENSION viewDimension, DXGI_FORMAT format);

	// Updates the render target view state.
	void 
	update();

  // Renders the scene using the render target view, clearing it with the specified color.
	void 
	render(DeviceContext& deviceContext, 
				DepthStencilView & depthStencilView, 
				unsigned int numViews, const float ClearColor[4]);

  // Renders the scene using the render target view without clearing it.
	void 
	render(DeviceContext& deviceContext, unsigned int numViews);

	// Releases the resources associated with the render target view.
	void 
	destroy();

private:
	ID3D11RenderTargetView* m_renderTargetView = nullptr;
};
