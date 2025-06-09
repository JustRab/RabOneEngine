#pragma once
#include "Prerequisites.h"

// Forward Declarations
class Device;
class DeviceContext;
class Window;
class Texture;

/**
 * @class SwapChain
 * @brief Manages the Direct3D swap chain for presenting rendered frames to the display.
 *
 * The SwapChain class encapsulates the creation, update, rendering, and destruction of a Direct3D swap chain.
 * It is responsible for presenting the rendered image to the screen and managing the back buffer.
 */
class
SwapChain {
public:
  /**
   * @brief Default constructor and destructor.
   */
  SwapChain() = default;
  ~SwapChain() = default;

  /**
   * @brief Initializes the swap chain with the given device, device context, back buffer texture, and window.
   * @param device Reference to the Direct3D device.
   * @param deviceContext Reference to the Direct3D device context.
   * @param backBuffer Reference to the back buffer texture.
   * @param window Reference to the window to associate with the swap chain.
   * @return HRESULT indicating success or failure of the initialization.
   */
  HRESULT
  init(Device& device,
      DeviceContext& deviceContext,
      Texture& backBuffer,
      Window window);

  /**
   * @brief Updates the swap chain state, if necessary.
   *
   * This method can be used to update internal state or resources related to the swap chain.
   */
  void
  update();

  /**
   * @brief Renders the current frame using the swap chain.
   *
   * This method performs any rendering operations required before presenting the frame.
   */
  void
  render();

  /**
   * @brief Destroys the swap chain and releases associated resources.
   *
   * This method releases the underlying Direct3D swap chain and related resources.
   */
  void
  destroy();

  /**
   * @brief Presents the current frame to the screen.
   *
   * This method displays the rendered image by swapping the back and front buffers.
   */
  void
  present();

  /**
   * @brief Pointer to the DirectX swap chain.
   */
  IDXGISwapChain* m_swapChain = nullptr;

  /**
   * @brief Type of the Direct3D driver being used.
   */
  D3D_DRIVER_TYPE m_driverType = D3D_DRIVER_TYPE_NULL;

private:

  /**
   * @brief Feature level of the Direct3D device.
   */
  D3D_FEATURE_LEVEL m_featureLevel = D3D_FEATURE_LEVEL_11_0;

  /**
   * @brief Number of MSAA samples (e.g., 4x MSAA).
   */
  unsigned int m_sampleCount; 
  /**
   * @brief Quality levels for MSAA.
   */
  unsigned int m_qualityLevels;

  // DXGI interface pointers
  IDXGIDevice* m_dxgiDevice = nullptr;
  IDXGIAdapter* m_dxgiAdapter = nullptr;
  IDXGIFactory* m_dxgiFactory = nullptr;
};