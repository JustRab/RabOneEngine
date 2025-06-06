#pragma once
#include "Prerequisites.h"

class 
Device {
public:
	Device() = default;
	~Device() = default;

  // Initializes the device setting up the resources needed for rendering.
	void 
	init();

	// Updates the device state.
	void 
	update();

  // Renders the current frame.
	void 
	render();

  // Cleans up the device and releases all allocated resources.
	void 
	destroy();

  // Creates a render target view from the given resource.
	HRESULT 
	CreateRenderTargetView(ID3D11Resource* pResource,
												const D3D11_RENDER_TARGET_VIEW_DESC* pDesc,
												ID3D11RenderTargetView** ppRTView);

  // Creates a 2D texture with the specified description and initial data.
	HRESULT 
	CreateTexture2D(const D3D11_TEXTURE2D_DESC* pDesc,
									const D3D11_SUBRESOURCE_DATA* pInitialData,
									ID3D11Texture2D** ppTexture2D);

  // Creates a depth stencil view from the given resource.
	HRESULT 
	CreateDepthStencilView(ID3D11Resource* pResource,
												const D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc,
												ID3D11DepthStencilView** ppDepthStencilView);

	// Creates a vertex shader.
	HRESULT 
	CreateVertexShader(const void* pShaderBytecode,
										SIZE_T BytecodeLength,
										ID3D11ClassLinkage* pClassLinkage,
										ID3D11VertexShader** ppVertexShader);

  // Creates an input layout based on the provided input element descriptions and shader bytecode for vertex data.
	HRESULT 
	CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* pInputElementDescs,
										UINT NumElements,
										const void* pShaderBytecodeWithInputSignature,
										SIZE_T BytecodeLength,
										ID3D11InputLayout** ppInputLayout);

  // Creates a pixel shader.
	HRESULT 
	CreatePixelShader(const void* pShaderBytecode,
										SIZE_T BytecodeLength,
										ID3D11ClassLinkage* pClassLinkage,
										ID3D11PixelShader** ppPixelShader);

  // Creates a sampler state object based on the specified sampler description.
	HRESULT
	CreateSamplerState(const D3D11_SAMPLER_DESC* pSamplerDesc,
										ID3D11SamplerState** ppSamplerState);

  // Creates a buffer resource with the specified description and initial data.
	HRESULT 
	CreateBuffer(const D3D11_BUFFER_DESC* pDesc,
							const D3D11_SUBRESOURCE_DATA* pInitialData,
							ID3D11Buffer** ppBuffer);

  // Creates a blend state object based on the specified blend state description.
	HRESULT 
	CreateBlendState(const D3D11_BLEND_DESC* pBlendStateDesc,
									ID3D11BlendState** ppBlendState);

  // Creates a depth stencil state object based on the specified depth stencil description.
	HRESULT 
	CreateDepthStencilState(const D3D11_DEPTH_STENCIL_DESC* pDepthStencilDesc,
													ID3D11DepthStencilState** ppDepthStencilState);

  // Creates a rasterizer state object based on the specified rasterizer description.
	HRESULT 
	CreateRasterizerState(const D3D11_RASTERIZER_DESC* pRasterizerDesc,
												ID3D11RasterizerState** ppRasterizerState);


	ID3D11Device* m_device = nullptr;
};
