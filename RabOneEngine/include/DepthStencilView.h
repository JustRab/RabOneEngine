#pragma once
#include "Prerequisites.h"

// Forward Declarations
class Device;
class DeviceContext;
class Texture;

/**
 * @class DepthStencilView
 * @brief Manages a Direct3D depth stencil view resource for depth and stencil testing.
 *
 * This class encapsulates the creation, update, rendering, and destruction of a depth stencil view.
 * It is used to manage depth and stencil buffers in the rendering pipeline.
 */
class
DepthStencilView {
public:
  /**
   * @brief Default constructor and destructor.
   */
DepthStencilView() = default;
~DepthStencilView() = default;

  /**
   * @brief Initializes the depth stencil view with the given device and texture.
   * @param device Reference to the device used to create the depth stencil view.
   * @param depthStencil Reference to the texture to be used as the depth stencil buffer.
   * @param format The DXGI_FORMAT to use for the depth stencil view.
   * @return HRESULT indicating success or failure of the initialization.
   */
  HRESULT
  init(Device& device, Texture& depthStencil, DXGI_FORMAT format);

  /**
   * @brief Updates the depth stencil view.
   *
   * This method can be used to update internal state or resources related to the depth stencil view.
   */
  void
  update();

  /**
   * @brief Renders using the depth stencil view.
   * @param deviceContext Reference to the device context used for rendering operations.
   *
   * This method binds the depth stencil view to the pipeline for rendering.
   */
  void
  render(DeviceContext& deviceContext);

  /**
   * @brief Destroys the depth stencil view and releases resources.
   *
   * This method releases the underlying Direct3D depth stencil view resource.
   */
  void
  destroy();

public:
  /**
   * @brief Pointer to the underlying Direct3D depth stencil view.
   */
  ID3D11DepthStencilView* m_depthStencilView = nullptr;

};

