#pragma once
#include "Prerequisites.h"
#include "Device.h"
#include "DeviceContext.h"

// Forward Declarations
class Device;
class DeviceContext;
class Texture;

class
Texture {
public:
  Texture() = default;
  ~Texture() = default;

  // Intializes a texture from file.
  HRESULT
  init(Device device, const std::string& textureName,
      ExtensionType extensionType);

  // Intializes a texture with specified parameters.
  HRESULT
  init(Device device,
       unsigned int width,
       unsigned int height,
       DXGI_FORMAT format,
       unsigned int BindFlags,
       unsigned int sampleCount = 1,
       unsigned int qualityLevels = 0);

  // Intializes a texture with a reference to another texture.
  HRESULT
  init(Device& device, Texture& textureRef,
      DXGI_FORMAT format);

  // Updates the texture data.
  void
  update();

  // Renders the texture using the device context.
  void
  render(DeviceContext& deviceContext,
         unsigned int StartSlot,
         unsigned int NumViews);

  // Releases texture resources and cleans up memory.
  void
  destroy();

public:
  // This variable is in charge of handle a texture resource as data
  ID3D11Texture2D* m_texture = nullptr;
  // This variable is in charge of handle a texture resource as image data
  ID3D11ShaderResourceView* m_textureFromImg;
};