#include "SamplerState.h"
#include "Device.h"
#include "DeviceContext.h"

HRESULT
SamplerState::init(Device& device) {
  if (!device.m_device) {
    ERROR("SamplerState", "init", "Device is nullptr");
    return E_POINTER;
  }

  D3D11_SAMPLER_DESC sampDesc = {};
  sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
  sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP; // Use WRAP for proper texture tiling
  sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP; // Use WRAP for proper texture tiling
  sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
  sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
  sampDesc.BorderColor[0] = 0.0f;
  sampDesc.BorderColor[1] = 0.0f;
  sampDesc.BorderColor[2] = 0.0f;
  sampDesc.BorderColor[3] = 0.0f;
  sampDesc.MinLOD = 0;
  sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
  sampDesc.MipLODBias = 0.0f;
  sampDesc.MaxAnisotropy = 1;

  HRESULT hr = device.CreateSamplerState(&sampDesc, &m_sampler);
  if (FAILED(hr)) {
    ERROR("SamplerState", "init", "Failed to create SamplerState");
    return hr;
  }

  return S_OK;
}

void
SamplerState::update() {
  // No hay lógica de actualización para un sampler en este caso.
}

void
SamplerState::render(DeviceContext& deviceContext,
  unsigned int StartSlot,
  unsigned int NumSamplers) {
  if (!m_sampler) {
    ERROR("SamplerState", "render", "SamplerState is nullptr");
    return;
  }

  deviceContext.PSSetSamplers(StartSlot, NumSamplers, &m_sampler);
}

void
SamplerState::destroy() {
  if (m_sampler) {
    SAFE_RELEASE(m_sampler);
  }
}