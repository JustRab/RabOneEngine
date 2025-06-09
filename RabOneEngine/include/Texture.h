#pragma once
#include "Prerequisites.h"
#include "Device.h"
#include "DeviceContext.h"

// Forward Declarations
class Device;
class DeviceContext;
class Texture;

/**
 * @class Texture
 * @brief Encapsulates a Direct3D texture resource and its associated views.
 *
 * The Texture class provides methods for initializing, updating, rendering, and destroying
 * Direct3D texture resources. It supports loading textures from files, creating textures
 * with custom parameters, and managing shader resource views for use in the rendering pipeline.
 */
class
Texture {
public:
  /**
   * @brief Default constructor and destructor.
   */
  Texture() = default;
  ~Texture() = default;

  /**
   * @brief Initializes a texture from a file.
   * @param device The Direct3D device used to create the texture.
   * @param textureName The file name of the texture to load.
   * @param extensionType The file extension type (e.g., DDS, PNG, JPG).
   * @return HRESULT indicating success or failure of the initialization.
   */
  HRESULT
  init(Device device, const std::string& textureName,
      ExtensionType extensionType);

  /**
   * @brief Initializes a texture with specified parameters.
   * @param device The Direct3D device used to create the texture.
   * @param width The width of the texture in pixels.
   * @param height The height of the texture in pixels.
   * @param format The DXGI_FORMAT of the texture.
   * @param BindFlags Flags specifying how the texture will be bound to the pipeline.
   * @param sampleCount Number of multisample anti-aliasing (MSAA) samples (default: 1).
   * @param qualityLevels MSAA quality levels (default: 0).
   * @return HRESULT indicating success or failure of the initialization.
   */
  HRESULT
  init(Device device,
       unsigned int width,
       unsigned int height,
       DXGI_FORMAT format,
       unsigned int BindFlags,
       unsigned int sampleCount = 1,
       unsigned int qualityLevels = 0);

  /**
   * @brief Initializes a texture using a reference to another texture.
   * @param device The Direct3D device used to create the texture.
   * @param textureRef Reference to another texture to use as a source.
   * @param format The DXGI_FORMAT for the new texture.
   * @return HRESULT indicating success or failure of the initialization.
   */
  HRESULT
  init(Device& device, Texture& textureRef,
      DXGI_FORMAT format);

  /**
   * @brief Updates the texture data.
   *
   * This method can be used to update the contents of the texture resource.
   */
  void
  update();

  /**
   * @brief Renders the texture using the device context.
   * @param deviceContext The device context used for rendering.
   * @param StartSlot The starting slot for binding the texture.
   * @param NumViews The number of shader resource views to bind.
   */
  void
  render(DeviceContext& deviceContext,
         unsigned int StartSlot,
         unsigned int NumViews);

  /**
   * @brief Releases texture resources and cleans up memory.
   *
   * This method releases the underlying Direct3D texture and shader resource view.
   */
  void
  destroy();

public:

  /**
   * @brief Pointer to the Direct3D texture resource.
   */
  ID3D11Texture2D* m_texture = nullptr;

  /**
   * @brief Pointer to the shader resource view for the texture.
   */
  ID3D11ShaderResourceView* m_textureFromImg;
};