#pragma once
#include "Prerequisites.h"

class Device;
class DeviceContext;

/**
 * @class Rasterizer
 * @brief Encapsulates the Direct3D rasterizer state for controlling how primitives are rendered.
 *
 * The Rasterizer class manages the creation, binding, and destruction of a Direct3D rasterizer state object.
 * This state controls how polygons are rasterized, including culling mode, fill mode, and other rasterization options.
 * It provides methods for initialization, updating, binding to the pipeline, and cleanup.
 */
class Rasterizer {
public:
  /**
   * @brief Default constructor.
   */
  Rasterizer() = default;

  /**
   * @brief Destructor.
   */
  ~Rasterizer() = default;

  /**
   * @brief Initializes the rasterizer state.
   * @param device The Direct3D device used to create the rasterizer state.
   * @return HRESULT indicating success or failure of the initialization.
   *
   * This method creates and configures the rasterizer state object.
   */
  HRESULT init(Device device);

  /**
   * @brief Updates the rasterizer state.
   *
   * This method can be used to update internal state or configuration if needed.
   */
  void update();

  /**
   * @brief Binds the rasterizer state to the device context for rendering.
   * @param deviceContext The device context to bind the rasterizer state to.
   *
   * This method sets the rasterizer state in the Direct3D pipeline.
   */
  void render(DeviceContext& deviceContext);

  /**
   * @brief Releases the rasterizer state and associated resources.
   *
   * This method should be called to clean up the rasterizer state when it is no longer needed.
   */
  void destroy();

private:
  ID3D11RasterizerState* m_rasterizerState = nullptr; ///< Pointer to the Direct3D rasterizer state object.
};
