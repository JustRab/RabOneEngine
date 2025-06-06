#pragma once
#include "Prerequisites.h"

// Forward Declarations
class Device;
class DeviceContext;
class Texture;

class 
DepthStencilView {
public:
	DepthStencilView() = default;
	~DepthStencilView() = default;

  // Initializes the depth stencil view with the given device and texture.
	HRESULT
	init(Device& device, Texture& depthStencil, DXGI_FORMAT format);

  // Updates the depth stencil view.
	void 
	update();

  // Renders using the depth stencil view.
	void 
	render(DeviceContext& deviceContext);

  // Destroys the depth stencil view and releases resources.
	void 
	destroy();

public:
	ID3D11DepthStencilView* m_depthStencilView = nullptr;

};

