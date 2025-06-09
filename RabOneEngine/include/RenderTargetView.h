#pragma once
#include "Prerequisites.h"

// Forward Declarations
class Device;
class DeviceContext;
class Texture;
class DepthStencilView;

/**
 * @class RenderTargetView
 * @brief Manages a Direct3D render target view resource for rendering output.
 *
 * This class encapsulates the creation, update, rendering, and destruction of a render target view.
 * It is used to manage render target buffers in the rendering pipeline.
 */
class
RenderTargetView {
public:
  /**
   * @brief Default constructor and destructor
   */
  RenderTargetView() = default;
  ~RenderTargetView() = default;

  /**
   * @brief Initializes the render target view with a back buffer texture and specified format.
   * @param device Reference to the device used to create the render target view.
   * @param backBuffer Reference to the texture to be used as the back buffer.
   * @param Format The DXGI_FORMAT to use for the render target view.
   * @return HRESULT indicating success or failure of the initialization.
   */
  HRESULT
  init(Device& device, Texture& backBuffer, DXGI_FORMAT Format);

  /**
   * @brief Initializes the render target view with a texture and specified view dimension and format.
   * @param device Reference to the device used to create the render target view.
   * @param inTex Reference to the texture to be used as the render target.
   * @param viewDimension The D3D11_RTV_DIMENSION to use for the render target view.
   * @param format The DXGI_FORMAT to use for the render target view.
   * @return HRESULT indicating success or failure of the initialization.
   */
  HRESULT
  init(Device& device, Texture& inTex,
      D3D11_RTV_DIMENSION viewDimension, DXGI_FORMAT format);

  /**
   * @brief Updates the render target view state.
   *
   * This method can be used to update internal state or resources related to the render target view.
   */
  void
  update();

  /**
   * @brief Renders the scene using the render target view, clearing it with the specified color.
   * @param deviceContext Reference to the device context used for rendering operations.
   * @param depthStencilView Reference to the depth stencil view to use during rendering.
   * @param numViews Number of render target views.
   * @param ClearColor Array of four floats representing the color to clear the render target with.
   */
  void
  render(DeviceContext& deviceContext,
        DepthStencilView& depthStencilView,
        unsigned int numViews, const float ClearColor[4]);

  /**
   * @brief Renders the scene using the render target view without clearing it.
   * @param deviceContext Reference to the device context used for rendering operations.
   * @param numViews Number of render target views.
   */
  void
  render(DeviceContext& deviceContext, unsigned int numViews);

  /**
   * @brief Releases the resources associated with the render target view.
   *
   * This method releases the underlying Direct3D render target view resource.
   */
  void
  destroy();

private:
  /**
   * @brief Pointer to the underlying Direct3D render target view.
   */
  ID3D11RenderTargetView* m_renderTargetView = nullptr;
};
