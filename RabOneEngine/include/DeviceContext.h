#pragma once
#include "Prerequisites.h"

class
DeviceContext {
public:
  DeviceContext() = default;
  ~DeviceContext() = default;

  // Initializes the device context.
  void
  init();

  // Updates the device context.
  void
  update();

  // Renders the current frame using device context.
  void
  render();

  // Destroys the device context and releases resources.
  void
  destroy();

  // Sets the input layout for the input assembler stage.
  void
  RSSetViewports(unsigned int NumViewports,
                const D3D11_VIEWPORT* pViewports);

  // Clears the depth-stencil view with the specified flags, depth, and stencil values.
  void
  ClearDepthStencilView(ID3D11DepthStencilView* pDepthStencilView,
                        unsigned int ClearFlags,
                        float Depth,
                        UINT8 Stencil);

  // Clears the render target view with the specified color.
  void
  ClearRenderTargetView(ID3D11RenderTargetView* pRenderTargetView,
                        const float ColorRGBA[4]);

  // Sets the render targets for the output merger stage.
  void
  OMSetRenderTargets(unsigned int NumViews,
                    ID3D11RenderTargetView* const* ppRenderTargetViews,
                    ID3D11DepthStencilView* pDepthStencilView);


  ID3D11DeviceContext* m_deviceContext = nullptr;
};