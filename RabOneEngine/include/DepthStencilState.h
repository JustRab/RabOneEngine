#pragma once
#include "Prerequisites.h"

class Device;
class DeviceContext;

/**
 * @class DepthStencilState
 * @brief Encapsulates a Direct3D depth-stencil state object and provides methods for initialization, binding, and cleanup.
 *
 * The DepthStencilState class manages the creation, usage, and destruction of a Direct3D depth-stencil state,
 * which controls depth and stencil testing in the output merger stage of the graphics pipeline.
 */
class 
DepthStencilState {
public:
  /**
   * @brief Default constructor.
   */
  DepthStencilState() = default;

  /**
   * @brief Destructor.
   */
  ~DepthStencilState() = default;

  /**
   * @brief Initializes the depth-stencil state using the provided device.
   * @param device Reference to the Direct3D device used to create the depth-stencil state.
   * @param enableDepth Enables depth testing if true. Defaults to true.
   * @param enableStencil Enables stencil testing if true. Defaults to false.
   * @return HRESULT indicating success or failure of the initialization.
   */
  HRESULT 
  init(Device& device, 
       bool enableDepth = true,
       bool enableStencil = false);

  /**
   * @brief Updates the depth-stencil state. (No-op in this implementation.)
   */
  void update();

  /**
   * @brief Binds the depth-stencil state to the output merger stage for rendering.
   * @param deviceContext Reference to the device context used for rendering.
   * @param stencilRef Reference value for stencil testing. Defaults to 0.
   * @param reset If true, resets the depth-stencil state to default. Defaults to false.
   */
  void 
  render(DeviceContext& deviceContext,
         unsigned int stencilRef = 0,
         bool reset = false);

  /**
   * @brief Releases the depth-stencil state and frees associated resources.
   */
  void destroy();

private:
  /**
   * @brief Pointer to the underlying Direct3D depth-stencil state object.
   */
  ID3D11DepthStencilState* m_depthStencilState = nullptr;
};
