#include "DeviceContext.h"

void
DeviceContext::init() {
  // Initialize device context if needed
}

void
DeviceContext::update() {
  // Update device context if needed
}

void
DeviceContext::render() {
  // Render using device context if needed
}

void
DeviceContext::destroy() {
  // Clean up device context if needed
}

void
DeviceContext::RSSetViewports(unsigned int NumViewports,
  const D3D11_VIEWPORT* pViewports) {
  if (NumViewports < 0 && pViewports != nullptr) {
    ERROR("DeviceContext", "RSSetViewports", "pViewports is nullptr");
  }
  // Set the Viewport
  m_deviceContext->RSSetViewports(NumViewports, pViewports);
}

void
DeviceContext::PSSetShaderResources(unsigned int StartSlot,
  unsigned int NumViews,
  ID3D11ShaderResourceView* const* ppShaderResourceViews) {
  if (m_deviceContext) {
    m_deviceContext->PSSetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
  }
}

void
DeviceContext::IASetInputLayout(ID3D11InputLayout* pInputLayout) {
  if (m_deviceContext) {
    m_deviceContext->IASetInputLayout(pInputLayout);
  }
}

void
DeviceContext::VSSetShader(ID3D11VertexShader* pVertexShader,
  ID3D11ClassInstance* const* ppClassInstances,
  unsigned int NumClassInstances) {
  if (m_deviceContext) {
    m_deviceContext->VSSetShader(pVertexShader, ppClassInstances, NumClassInstances);
  }
}

void
DeviceContext::PSSetShader(ID3D11PixelShader* pPixelShader,
  ID3D11ClassInstance* const* ppClassInstances,
  unsigned int NumClassInstances) {
  if (m_deviceContext) {
    m_deviceContext->PSSetShader(pPixelShader, ppClassInstances, NumClassInstances);
  }
}

void
DeviceContext::UpdateSubresource(ID3D11Resource* pDstResource,
  unsigned int DstSubresource,
  const D3D11_BOX* pDstBox,
  const void* pSrcData,
  unsigned int SrcRowPitch,
  unsigned int SrcDepthPitch) {
  if (m_deviceContext) {
    m_deviceContext->UpdateSubresource(pDstResource, DstSubresource, pDstBox, pSrcData, SrcRowPitch, SrcDepthPitch);
  }
}

void
DeviceContext::IASetVertexBuffers(unsigned int StartSlot,
  unsigned int NumBuffers,
  ID3D11Buffer* const* ppVertexBuffers,
  const unsigned int* pStrides,
  const unsigned int* pOffsets) {
  if (m_deviceContext) {
    m_deviceContext->IASetVertexBuffers(StartSlot, NumBuffers, ppVertexBuffers, pStrides, pOffsets);
  }
}

void
DeviceContext::IASetIndexBuffer(ID3D11Buffer* pIndexBuffer,
  DXGI_FORMAT Format,
  unsigned int Offset) {
  if (m_deviceContext) {
    m_deviceContext->IASetIndexBuffer(pIndexBuffer, Format, Offset);
  }
}

void
DeviceContext::PSSetSamplers(unsigned int StartSlot,
  unsigned int NumSamplers,
  ID3D11SamplerState* const* ppSamplers) {
  if (m_deviceContext) {
    m_deviceContext->PSSetSamplers(StartSlot, NumSamplers, ppSamplers);
  }
}

void
DeviceContext::RSSetState(ID3D11RasterizerState* pRasterizerState) {
  if (m_deviceContext) {
    m_deviceContext->RSSetState(pRasterizerState);
  }
}

void
DeviceContext::OMSetBlendState(ID3D11BlendState* pBlendState,
  const float BlendFactor[4],
  unsigned int SampleMask) {
  if (m_deviceContext) {
    m_deviceContext->OMSetBlendState(pBlendState, BlendFactor, SampleMask);
  }
}

void
DeviceContext::ClearDepthStencilView(ID3D11DepthStencilView* pDepthStencilView,
  unsigned int ClearFlags,
  float Depth,
  UINT8 Stencil) {
  if (m_deviceContext) {
    m_deviceContext->ClearDepthStencilView(pDepthStencilView, ClearFlags, Depth, Stencil);
  }
}

void
DeviceContext::ClearRenderTargetView(ID3D11RenderTargetView* pRenderTargetView,
  const float ColorRGBA[4]) {
  if (m_deviceContext) {
    m_deviceContext->ClearRenderTargetView(pRenderTargetView, ColorRGBA);
  }
}

void
DeviceContext::OMSetRenderTargets(unsigned int NumViews,
  ID3D11RenderTargetView* const* ppRenderTargetViews,
  ID3D11DepthStencilView* pDepthStencilView) {
  if (m_deviceContext) {
    m_deviceContext->OMSetRenderTargets(NumViews, ppRenderTargetViews, pDepthStencilView);
  }
}

void
DeviceContext::IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY Topology) {
  if (m_deviceContext) {
    m_deviceContext->IASetPrimitiveTopology(Topology);
  }
}

void
DeviceContext::VSSetConstantBuffers(unsigned int StartSlot,
  unsigned int NumBuffers,
  ID3D11Buffer* const* ppConstantBuffers) {
  if (m_deviceContext) {
    m_deviceContext->VSSetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
  }
}

void
DeviceContext::PSSetConstantBuffers(unsigned int StartSlot,
  unsigned int NumBuffers,
  ID3D11Buffer* const* ppConstantBuffers) {
  if (m_deviceContext) {
    m_deviceContext->PSSetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
  }
}

void
DeviceContext::DrawIndexed(unsigned int IndexCount,
  unsigned int StartIndexLocation,
  int BaseVertexLocation) {
  if (m_deviceContext) {
    m_deviceContext->DrawIndexed(IndexCount, StartIndexLocation, BaseVertexLocation);
  }
}

