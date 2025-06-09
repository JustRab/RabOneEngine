#pragma once
#include "Prerequisites.h"

/**
 * @class Device
 * @brief Encapsulates the Direct3D device and provides methods for resource creation and management.
 *
 * The Device class is responsible for initializing and managing the Direct3D device, as well as creating
 * various graphics resources such as textures, buffers, shaders, and state objects required for rendering.
 */
class
Device {
public:
  /**
   * @brief Default constructor and destructor.
   */
  Device() = default;
  ~Device() = default;

  /**
   * @brief Initializes the device and sets up the resources needed for rendering.
   */
  void
  init();

  /**
   * @brief Updates the device state.
   */
  void
  update();

  /**
   * @brief Renders the current frame.
   */
  void
  render();

  /**
   * @brief Cleans up the device and releases all allocated resources.
   */
  void
  destroy();

  /**
   * @brief Creates a render target view from the given resource.
   * @param pResource Pointer to the resource to be used as a render target.
   * @param pDesc Optional description of the render target view.
   * @param ppRTView Address of a pointer to the created render target view.
   * @return HRESULT indicating success or failure.
   */
  HRESULT
  CreateRenderTargetView(ID3D11Resource* pResource,
                        const D3D11_RENDER_TARGET_VIEW_DESC* pDesc,
                        ID3D11RenderTargetView** ppRTView);

  /**
   * @brief Creates a 2D texture with the specified description and initial data.
   * @param pDesc Pointer to the texture description.
   * @param pInitialData Optional pointer to initial data.
   * @param ppTexture2D Address of a pointer to the created texture.
   * @return HRESULT indicating success or failure.
   */
  HRESULT
  CreateTexture2D(const D3D11_TEXTURE2D_DESC* pDesc,
                  const D3D11_SUBRESOURCE_DATA* pInitialData,
                  ID3D11Texture2D** ppTexture2D);

  /**
   * @brief Creates a depth stencil view from the given resource.
   * @param pResource Pointer to the resource to be used as a depth stencil.
   * @param pDesc Optional description of the depth stencil view.
   * @param ppDepthStencilView Address of a pointer to the created depth stencil view.
   * @return HRESULT indicating success or failure.
   */
  HRESULT
  CreateDepthStencilView(ID3D11Resource* pResource,
                         const D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc,
                         ID3D11DepthStencilView** ppDepthStencilView);

  /**
   * @brief Creates a vertex shader.
   * @param pShaderBytecode Pointer to the compiled shader bytecode.
   * @param BytecodeLength Length of the shader bytecode.
   * @param pClassLinkage Optional class linkage interface.
   * @param ppVertexShader Address of a pointer to the created vertex shader.
   * @return HRESULT indicating success or failure.
   */
  HRESULT
  CreateVertexShader(const void* pShaderBytecode,
                     SIZE_T BytecodeLength,
                     ID3D11ClassLinkage* pClassLinkage,
                     ID3D11VertexShader** ppVertexShader);

  /**
   * @brief Creates an input layout based on the provided input element descriptions and shader bytecode for vertex data.
   * @param pInputElementDescs Array of input element descriptions.
   * @param NumElements Number of elements in the array.
   * @param pShaderBytecodeWithInputSignature Pointer to the compiled shader bytecode.
   * @param BytecodeLength Length of the shader bytecode.
   * @param ppInputLayout Address of a pointer to the created input layout.
   * @return HRESULT indicating success or failure.
   */
  HRESULT
  CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* pInputElementDescs,
                    UINT NumElements,
                    const void* pShaderBytecodeWithInputSignature,
                    SIZE_T BytecodeLength,
                    ID3D11InputLayout** ppInputLayout);

  /**
   * @brief Creates a pixel shader.
   * @param pShaderBytecode Pointer to the compiled shader bytecode.
   * @param BytecodeLength Length of the shader bytecode.
   * @param pClassLinkage Optional class linkage interface.
   * @param ppPixelShader Address of a pointer to the created pixel shader.
   * @return HRESULT indicating success or failure.
   */
  HRESULT
  CreatePixelShader(const void* pShaderBytecode,
                    SIZE_T BytecodeLength,
                    ID3D11ClassLinkage* pClassLinkage,
                    ID3D11PixelShader** ppPixelShader);

  /**
   * @brief Creates a sampler state object based on the specified sampler description.
   * @param pSamplerDesc Pointer to the sampler description.
   * @param ppSamplerState Address of a pointer to the created sampler state.
   * @return HRESULT indicating success or failure.
   */
  HRESULT
  CreateSamplerState(const D3D11_SAMPLER_DESC* pSamplerDesc,
                     ID3D11SamplerState** ppSamplerState);

  /**
   * @brief Creates a buffer resource with the specified description and initial data.
   * @param pDesc Pointer to the buffer description.
   * @param pInitialData Optional pointer to initial data.
   * @param ppBuffer Address of a pointer to the created buffer.
   * @return HRESULT indicating success or failure.
   */
  HRESULT
  CreateBuffer(const D3D11_BUFFER_DESC* pDesc,
               const D3D11_SUBRESOURCE_DATA* pInitialData,
               ID3D11Buffer** ppBuffer);

  /**
   * @brief Creates a blend state object based on the specified blend state description.
   * @param pBlendStateDesc Pointer to the blend state description.
   * @param ppBlendState Address of a pointer to the created blend state.
   * @return HRESULT indicating success or failure.
   */
  HRESULT
  CreateBlendState(const D3D11_BLEND_DESC* pBlendStateDesc,
                   ID3D11BlendState** ppBlendState);

  /**
   * @brief Creates a depth stencil state object based on the specified depth stencil description.
   * @param pDepthStencilDesc Pointer to the depth stencil state description.
   * @param ppDepthStencilState Address of a pointer to the created depth stencil state.
   * @return HRESULT indicating success or failure.
   */
  HRESULT
  CreateDepthStencilState(const D3D11_DEPTH_STENCIL_DESC* pDepthStencilDesc,
                          ID3D11DepthStencilState** ppDepthStencilState);

  /**
   * @brief Creates a rasterizer state object based on the specified rasterizer description.
   * @param pRasterizerDesc Pointer to the rasterizer state description.
   * @param ppRasterizerState Address of a pointer to the created rasterizer state.
   * @return HRESULT indicating success or failure.
   */
  HRESULT
  CreateRasterizerState(const D3D11_RASTERIZER_DESC* pRasterizerDesc,
                        ID3D11RasterizerState** ppRasterizerState);

  /**
   * @brief Pointer to the underlying Direct3D device.
   */
  ID3D11Device* m_device = nullptr;
};
