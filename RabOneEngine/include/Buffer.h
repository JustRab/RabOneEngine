#pragma once
#include "Prerequisites.h"

class Device;
class DeviceContext;
class MeshComponent;

/**
 * @class Buffer
 * @brief Encapsulates a Direct3D buffer resource and provides methods for initialization, updating, rendering, and cleanup.
 *
 * The Buffer class manages vertex, index, and constant buffers for use in the Direct3D rendering pipeline.
 * It supports initialization from mesh data or as a constant buffer, updating buffer contents, binding for rendering,
 * and resource destruction.
 */
class 
Buffer {
public:
  /**
   * @brief Default constructor.
   */
  Buffer() = default;

  /**
   * @brief Destructor.
   */
  ~Buffer() = default;

  /**
   * @brief Initializes a vertex or index buffer from mesh data.
   * @param device Reference to the Direct3D device used to create the buffer.
   * @param mesh Reference to the mesh component containing vertex or index data.
   * @param bindFlag Buffer binding flag (e.g., D3D11_BIND_VERTEX_BUFFER or D3D11_BIND_INDEX_BUFFER).
   * @return HRESULT indicating success or failure of the initialization.
   */
  HRESULT 
  init(Device& device, 
       const MeshComponent& mesh, 
       unsigned int bindFlag);

  /**
   * @brief Initializes a constant buffer with the specified size.
   * @param device Reference to the Direct3D device used to create the buffer.
   * @param ByteWidth Size of the buffer in bytes.
   * @return HRESULT indicating success or failure of the initialization.
   */
  HRESULT 
  init(Device& device, 
       unsigned int ByteWidth);

  /**
   * @brief Updates the contents of a constant buffer.
   * @param deviceContext Reference to the device context used for updating the buffer.
   * @param pDstResource Pointer to the destination resource to update.
   * @param DstSubresource Index of the destination subresource.
   * @param pDstBox Optional pointer to a box defining the region to update. Can be nullptr for the whole resource.
   * @param pSrcData Pointer to the source data to copy into the buffer.
   * @param SrcRowPitch Row pitch of the source data.
   * @param SrcDepthPitch Depth pitch of the source data.
   */
  void 
  update(DeviceContext& deviceContext,
         ID3D11Resource* pDstResource,
         unsigned int DstSubresource,
         const D3D11_BOX* pDstBox,
         const void* pSrcData,
         unsigned int SrcRowPitch,
         unsigned int SrcDepthPitch);

  /**
   * @brief Binds the buffer to the input assembler or shader stage for rendering.
   * @param deviceContext Reference to the device context used for rendering.
   * @param StartSlot The first input slot for binding the buffer.
   * @param NumBuffers Number of buffers to bind.
   * @param setPixelShader If true, binds the buffer to the pixel shader stage. Defaults to false.
   * @param format Optional DXGI_FORMAT for index buffers. Defaults to DXGI_FORMAT_UNKNOWN.
   */
  void
  render(DeviceContext& deviceContext,
         unsigned int StartSlot,
         unsigned int NumBuffers,
         bool setPixelShader = false,
         DXGI_FORMAT format = DXGI_FORMAT_UNKNOWN);

  /**
   * @brief Releases the buffer and frees associated resources.
   */
  void
  destroy();

  /**
   * @brief Creates a Direct3D buffer with the specified description and initial data.
   * @param device Reference to the Direct3D device used to create the buffer.
   * @param desc Reference to the buffer description structure.
   * @param initData Optional pointer to initial data for the buffer.
   * @return HRESULT indicating success or failure of the buffer creation.
   */
  HRESULT 
  createBuffer(Device& device,
               D3D11_BUFFER_DESC& desc,
               D3D11_SUBRESOURCE_DATA* initData);

private:
  /**
   * @brief Pointer to the underlying Direct3D buffer resource.
   */
  ID3D11Buffer* m_buffer = nullptr;

  /**
   * @brief Stride (in bytes) of the buffer elements (used for vertex buffers).
   */
  unsigned int m_stride = 0;

  /**
   * @brief Offset (in bytes) from the start of the buffer (used for binding).
   */
  unsigned int m_offset = 0;

  /**
   * @brief Buffer binding flag (e.g., vertex, index, or constant buffer).
   */
  unsigned int m_bindFlag = 0;
};
