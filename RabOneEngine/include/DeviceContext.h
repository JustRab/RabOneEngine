#pragma once
#include "Prerequisites.h"

/**
 * @class DeviceContext
 * @brief Manages the Direct3D device context for rendering operations.
 *
 * The DeviceContext class encapsulates the Direct3D device context, providing methods to control
 * rendering, resource management, and pipeline state. It is responsible for issuing rendering commands
 * and managing the state of the graphics pipeline.
 */
class DeviceContext {
public:
  /**
   * @brief Default constructor.
   */
  DeviceContext() = default;

  /**
   * @brief Destructor.
   */
  ~DeviceContext() = default;

  /**
   * @brief Initializes the device context.
   *
   * Sets up the device context for use in rendering operations.
   */
  void init();

  /**
   * @brief Updates the device context.
   *
   * Updates any internal state or resources associated with the device context.
   */
  void update();

  /**
   * @brief Renders the current frame using the device context.
   *
   * Issues rendering commands for the current frame.
   */
  void render();

  /**
   * @brief Destroys the device context and releases resources.
   *
   * Cleans up and releases all resources associated with the device context.
   */
  void destroy();

  /**
   * @brief Sets the viewports for the rasterizer stage.
   * @param NumViewports Number of viewports to set.
   * @param pViewports Pointer to an array of D3D11_VIEWPORT structures.
   */
  void RSSetViewports(unsigned int NumViewports,
    const D3D11_VIEWPORT* pViewports);

  /**
   * @brief Sets shader resources for the pixel shader stage.
   * @param StartSlot The first slot to bind.
   * @param NumViews Number of shader resource views to bind.
   * @param ppShaderResourceViews Array of pointers to shader resource views.
   */
  void PSSetShaderResources(unsigned int StartSlot,
    unsigned int NumViews,
    ID3D11ShaderResourceView* const* ppShaderResourceViews);

  /**
   * @brief Sets the input layout for the input assembler stage.
   * @param pInputLayout Pointer to the input layout object.
   */
  void IASetInputLayout(ID3D11InputLayout* pInputLayout);

  /**
   * @brief Sets the vertex shader for the pipeline.
   * @param pVertexShader Pointer to the vertex shader.
   * @param ppClassInstances Array of class instances for shader interfaces.
   * @param NumClassInstances Number of class instances.
   */
  void VSSetShader(ID3D11VertexShader* pVertexShader,
    ID3D11ClassInstance* const* ppClassInstances,
    unsigned int NumClassInstances);

  /**
   * @brief Sets the pixel shader for the pipeline.
   * @param pPixelShader Pointer to the pixel shader.
   * @param ppClassInstances Array of class instances for shader interfaces.
   * @param NumClassInstances Number of class instances.
   */
  void PSSetShader(ID3D11PixelShader* pPixelShader,
    ID3D11ClassInstance* const* ppClassInstances,
    unsigned int NumClassInstances);

  /**
   * @brief Updates a subresource, such as a buffer or texture.
   * @param pDstResource Pointer to the destination resource.
   * @param DstSubresource Index of the destination subresource.
   * @param pDstBox Optional pointer to a box defining the region to update. Can be nullptr for the whole resource.
   * @param pSrcData Pointer to the source data to copy into the resource.
   * @param SrcRowPitch Row pitch of the source data.
   * @param SrcDepthPitch Depth pitch of the source data.
   */
  void UpdateSubresource(ID3D11Resource* pDstResource,
    unsigned int DstSubresource,
    const D3D11_BOX* pDstBox,
    const void* pSrcData,
    unsigned int SrcRowPitch,
    unsigned int SrcDepthPitch);

  /**
   * @brief Sets the vertex buffers for the input assembler stage.
   * @param StartSlot The first input slot for binding.
   * @param NumBuffers Number of buffers to bind.
   * @param ppVertexBuffers Array of pointers to vertex buffers.
   * @param pStrides Array of stride values for each buffer.
   * @param pOffsets Array of offset values for each buffer.
   */
  void IASetVertexBuffers(unsigned int StartSlot,
    unsigned int NumBuffers,
    ID3D11Buffer* const* ppVertexBuffers,
    const unsigned int* pStrides,
    const unsigned int* pOffsets);

  /**
   * @brief Sets the index buffer for the input assembler stage.
   * @param pIndexBuffer Pointer to the index buffer.
   * @param Format Format of the index data (e.g., DXGI_FORMAT_R16_UINT).
   * @param Offset Offset (in bytes) from the start of the buffer.
   */
  void IASetIndexBuffer(ID3D11Buffer* pIndexBuffer,
    DXGI_FORMAT Format,
    unsigned int Offset);

  /**
   * @brief Sets the sampler states for the pixel shader stage.
   * @param StartSlot The first sampler slot to bind.
   * @param NumSamplers Number of sampler states to bind.
   * @param ppSamplers Array of pointers to sampler state objects.
   */
  void PSSetSamplers(unsigned int StartSlot,
    unsigned int NumSamplers,
    ID3D11SamplerState* const* ppSamplers);

  /**
   * @brief Sets the rasterizer state.
   * @param pRasterizerState Pointer to the rasterizer state object.
   */
  void RSSetState(ID3D11RasterizerState* pRasterizerState);

  /**
   * @brief Sets the blend state for the output merger stage.
   * @param pBlendState Pointer to the blend state object.
   * @param BlendFactor Array of blend factors.
   * @param SampleMask Sample mask for multisample anti-aliasing.
   */
  void OMSetBlendState(ID3D11BlendState* pBlendState,
    const float BlendFactor[4],
    unsigned int SampleMask);

  /**
   * @brief Clears the depth-stencil view with the specified flags, depth, and stencil values.
   * @param pDepthStencilView Pointer to the depth-stencil view to clear.
   * @param ClearFlags Flags indicating which part of the depth-stencil view to clear.
   * @param Depth Value to clear the depth buffer with.
   * @param Stencil Value to clear the stencil buffer with.
   */
  void ClearDepthStencilView(ID3D11DepthStencilView* pDepthStencilView,
    unsigned int ClearFlags,
    float Depth,
    UINT8 Stencil);

  /**
   * @brief Clears the render target view with the specified color.
   * @param pRenderTargetView Pointer to the render target view to clear.
   * @param ColorRGBA Array of four floats representing the color to clear with.
   */
  void ClearRenderTargetView(ID3D11RenderTargetView* pRenderTargetView,
    const float ColorRGBA[4]);

  /**
   * @brief Sets the render targets for the output merger stage.
   * @param NumViews Number of render target views.
   * @param ppRenderTargetViews Array of pointers to render target views.
   * @param pDepthStencilView Pointer to the depth-stencil view.
   */
  void OMSetRenderTargets(unsigned int NumViews,
    ID3D11RenderTargetView* const* ppRenderTargetViews,
    ID3D11DepthStencilView* pDepthStencilView);

  /**
   * @brief Sets the primitive topology for the input assembler stage.
   * @param Topology The primitive topology (e.g., triangle list, line strip).
   */
  void IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY Topology);

  /**
   * @brief Sets constant buffers for the vertex shader stage.
   * @param StartSlot The first constant buffer slot to bind.
   * @param NumBuffers Number of constant buffers to bind.
   * @param ppConstantBuffers Array of pointers to constant buffer objects.
   */
  void VSSetConstantBuffers(unsigned int StartSlot,
    unsigned int NumBuffers,
    ID3D11Buffer* const* ppConstantBuffers);

  /**
   * @brief Sets constant buffers for the pixel shader stage.
   * @param StartSlot The first constant buffer slot to bind.
   * @param NumBuffers Number of constant buffers to bind.
   * @param ppConstantBuffers Array of pointers to constant buffer objects.
   */
  void PSSetConstantBuffers(unsigned int StartSlot,
    unsigned int NumBuffers,
    ID3D11Buffer* const* ppConstantBuffers);

  /**
   * @brief Draws indexed, instanced primitives.
   * @param IndexCount Number of indices to draw.
   * @param StartIndexLocation Index of the first index to use.
   * @param BaseVertexLocation Value added to each index before reading a vertex from the vertex buffer.
   */
  void DrawIndexed(unsigned int IndexCount,
    unsigned int StartIndexLocation,
    int BaseVertexLocation);

public:
  /**
   * @brief Pointer to the underlying Direct3D device context.
   */
  ID3D11DeviceContext* m_deviceContext = nullptr;
};
