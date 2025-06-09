#pragma once
#include "Prerequisites.h"

/**
 * @class Viewport
 * @brief Manages a Direct3D viewport, defining the drawable region of the render target.
 *
 * The Viewport class encapsulates the initialization, update, rendering, and destruction
 * of a D3D11_VIEWPORT structure. It allows configuration based on a window or explicit dimensions
 * and provides methods to bind the viewport to a device context for rendering.
 */
class Window;
class DeviceContext;

class
Viewport {
public:

  /**
   * @brief Default constructor and destructor.
   */
  Viewport() = default;
  ~Viewport() = default;

  /**
   * @brief Initializes the viewport using a Window instance.
   * @param window Reference to the Window object whose dimensions will be used.
   * @return HRESULT indicating success or failure of the initialization.
   */
  HRESULT
  init(const Window& window);

  /**
   * @brief Initializes the viewport with the specified dimensions.
   * @param width The width of the viewport in pixels.
   * @param height The height of the viewport in pixels.
   * @return HRESULT indicating success or failure of the initialization.
   */
  HRESULT
  init(unsigned int width, unsigned int height);

  /**
   * @brief Updates the viewport settings when any changes to the dimensions are required.
   *
   * This method should be called if the viewport size or parameters need to be refreshed.
   */
  void
  update();

  /**
   * @brief Renders the viewport using the given DeviceContext.
   * @param deviceContext Reference to the DeviceContext used to set the viewport.
   *
   * This method binds the viewport to the device context for subsequent rendering operations.
   */
  void
  render(DeviceContext& deviceContext);

  /**
   * @brief Releases the resources from the viewport.
   *
   * This method cleans up any resources associated with the viewport.
   */
  void
  destroy();

public:

  /**
   * @brief The underlying D3D11_VIEWPORT structure.
   */
  D3D11_VIEWPORT m_viewport;
};