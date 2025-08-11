#pragma once
#include "Prerequisites.h"

// Forward declarations
class Device;
class DeviceContext;

/**
 * @class SamplerState
 * @brief Manages DirectX 11 sampler state for texture sampling operations.
 */
class SamplerState {
public:
  /**
   * @brief Constructs a new SamplerState instance.
   */
  SamplerState() = default;

  /**
   * @brief Destroys the SamplerState instance and releases any held resources.
   */
  ~SamplerState() { destroy(); }

  /**
   * @brief Initializes the sampler state with default settings.
   * @param device The Device to create the sampler state with.
   * @return HRESULT indicating success or failure of initialization.
   */
  HRESULT 
  init(Device& device);

  /**
   * @brief Updates the sampler state (placeholder for future functionality).
   */
  void 
  update();

  /**
   * @brief Renders/binds the sampler state to the pipeline.
   * @param deviceContext The device context to render with.
   * @param StartSlot The starting slot to bind the sampler to.
   * @param NumSamplers The number of samplers to bind.
   */
  void 
  render(DeviceContext& deviceContext,
         unsigned int StartSlot,
         unsigned int NumSamplers);

  /**
   * @brief Releases the sampler state resources.
   */
  void 
  destroy();

public:
  ID3D11SamplerState* m_sampler = nullptr; ///< DirectX 11 sampler state object.
};