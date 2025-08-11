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
class
  DeviceContext {
public:
  /**
   * @brief Default constructor and destructor.
   */
  DeviceContext() = default;
  ~DeviceContext() = default;

  /**
   * @brief Initializes the device context.
   */
  void
    init();

  /**
   * @brief Updates the device context.
   */
  void
    update();

  /**
   * @brief Renders the current frame using the device context.
   */
  void
    render();

  /**
   * @brief Destroys the device context and releases resources.
   */
  void
    destroy();

  /**
   * @brief Sets the input layout for the input assembler stage.
   * @param NumViewports Number of viewports to set.
   * @param pViewports Pointer to an array of D3D11_VIEWPORT structures.
   */
  void
  RSSetViewports(unsigned int NumViewports,
                 const D3D11_VIEWPORT* pViewports);


  void
  PSSetShaderResources(unsigned int StartSlot,
                       unsigned int NumViews,
                       ID3D11ShaderResourceView* const* ppShaderResourceViews);

  void
  IASetInputLayout(ID3D11InputLayout* pInputLayout);

  void
  VSSetShader(ID3D11VertexShader* pVertexShader,
      ID3D11ClassInstance* const* ppClassInstances,
      unsigned int NumClassInstances);
  void
  PSSetShader(ID3D11PixelShader* pPixelShader,
      ID3D11ClassInstance* const* ppClassInstances,
      unsigned int NumClassInstances);

  void
  UpdateSubresource(ID3D11Resource* pDstResource,
      unsigned int DstSubresource,
      const D3D11_BOX* pDstBox,
      const void* pSrcData,
      unsigned int SrcRowPitch,
      unsigned int SrcDepthPitch);

  void
  IASetVertexBuffers(unsigned int StartSlot,
      unsigned int NumBuffers,
      ID3D11Buffer* const* ppVertexBuffers,
      const unsigned int* pStrides,
      const unsigned int* pOffsets);

  void
  IASetIndexBuffer(ID3D11Buffer* pIndexBuffer,
      DXGI_FORMAT Format,
      unsigned int Offset);

  void
  PSSetSamplers(unsigned int StartSlot,
      unsigned int NumSamplers,
      ID3D11SamplerState* const* ppSamplers);

  void
  RSSetState(ID3D11RasterizerState* pRasterizerState);

  void
  OMSetBlendState(ID3D11BlendState* pBlendState,
      const float BlendFactor[4],
      unsigned int SampleMask);

  /**
   * @brief Clears the depth-stencil view with the specified flags, depth, and stencil values.
   * @param pDepthStencilView Pointer to the depth-stencil view to clear.
   * @param ClearFlags Flags indicating which part of the depth-stencil view to clear.
   * @param Depth Value to clear the depth buffer with.
   * @param Stencil Value to clear the stencil buffer with.
   */
  void
  ClearDepthStencilView(ID3D11DepthStencilView* pDepthStencilView,
                        unsigned int ClearFlags,
                        float Depth,
                        UINT8 Stencil);

  /**
   * @brief Clears the render target view with the specified color.
   * @param pRenderTargetView Pointer to the render target view to clear.
   * @param ColorRGBA Array of four floats representing the color to clear with.
   */
  void
  ClearRenderTargetView(ID3D11RenderTargetView* pRenderTargetView,
                        const float ColorRGBA[4]);

  /**
   * @brief Sets the render targets for the output merger stage.
   * @param NumViews Number of render target views.
   * @param ppRenderTargetViews Array of pointers to render target views.
   * @param pDepthStencilView Pointer to the depth-stencil view.
   */
  void
  OMSetRenderTargets(unsigned int NumViews,
                     ID3D11RenderTargetView* const* ppRenderTargetViews,
                     ID3D11DepthStencilView* pDepthStencilView);
  void
  IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY Topology);

  void
  VSSetConstantBuffers(unsigned int StartSlot,
                       unsigned int NumBuffers,
                       ID3D11Buffer* const* ppConstantBuffers);

  void
  PSSetConstantBuffers(unsigned int StartSlot,
                       unsigned int NumBuffers,
                       ID3D11Buffer* const* ppConstantBuffers);
  void
  DrawIndexed(unsigned int IndexCount,
              unsigned int StartIndexLocation,
              int BaseVertexLocation);

public:
  /**
   * @brief Pointer to the underlying Direct3D device context.
   */
  ID3D11DeviceContext* m_deviceContext = nullptr;
};