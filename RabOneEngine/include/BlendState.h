#pragma once
#include "Prerequisites.h"

class Device;
class DeviceContext;

/**
 * @class BlendState
 * @brief Encapsulates a Direct3D blend state object and provides methods for initialization, binding, and cleanup.
 *
 * The BlendState class manages the creation, usage, and destruction of a Direct3D blend state,
 * which controls how pixel colors are blended in the output merger stage of the graphics pipeline.
 */
class BlendState {
public:
  /**
   * @brief Default constructor.
   */
  BlendState() = default;

  /**
   * @brief Destructor.
   */
  ~BlendState() = default;

  /**
   * @brief Initializes the blend state using the provided device.
   * @param device Reference to the Direct3D device used to create the blend state.
   * @return HRESULT indicating success or failure of the initialization.
   */
  HRESULT 
  init(Device& device);

  /**
   * @brief Updates the blend state. (No-op in this implementation.)
   */
  void 
  update() {};

  /**
   * @brief Binds the blend state to the output merger stage for rendering.
   * @param deviceContext Reference to the device context used for rendering.
   * @param blendFactor Optional pointer to a four-component blend factor array. Defaults to nullptr.
   * @param sampleMask Optional sample mask. Defaults to 0xffffffff.
   * @param reset If true, resets the blend state to default. Defaults to false.
   */
  void 
  render(DeviceContext& deviceContext,
         float* blendFactor = nullptr,
         unsigned int sampleMask = 0xffffffff,
         bool reset = false);

  /**
   * @brief Releases the blend state and frees associated resources.
   */
  void 
  destroy();

private:
  /**
   * @brief Pointer to the underlying Direct3D blend state object.
   */
  ID3D11BlendState* m_blendState = nullptr;
};
