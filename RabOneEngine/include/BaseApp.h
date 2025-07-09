#pragma once
#include "Prerequisites.h"
#include "Window.h"
#include "Device.h"
#include "DeviceContext.h"
#include "Texture.h"
#include "SwapChain.h"
#include "RenderTargetView.h"
#include "DepthStencilView.h"
#include "Viewport.h"
#include "InputLayout.h"
#include "ShaderProgram.h"
#include "Buffer.h"
#include "MeshComponent.h"
#include "BlendState.h"
#include "DepthStencilState.h"

/**
 * @class BaseApp
 * @brief Provides the base interface for an application, including initialization, update, rendering, cleanup, and execution.
 *
 * This class serves as the foundation for applications, managing the main lifecycle and resource handling.
 */
class
BaseApp {
public:
  /**
   * @brief Constructs a new BaseApp instance.
   */
  BaseApp() = default;
  /**
   * @brief Destroys the BaseApp instance and releases any held resources.
   */
  ~BaseApp() = default;

  /**
   * @brief Initializes the application by setting up the necessary resources.
   * @return HRESULT indicating success or failure of initialization.
   */
  HRESULT
  init();

  /**
   * @brief Updates the application logic each frame.
   */
  void
  update();

  /**
   * @brief Renders the application content to the screen.
   */
  void
  render();

  /**
   * @brief Releases all resources and cleans up the application to free memory before exiting.
   */
  void 
  destroy();

  /**
   * @brief Runs the application from the main entry point.
   * @param hInstance Handle to the current instance of the application.
   * @param hPrevInstance Handle to the previous instance of the application (always NULL).
   * @param lpCmdLine Command line arguments as a Unicode string.
   * @param nCmdShow Controls how the window is to be shown.
   * @param wndproc Window procedure function pointer.
   * @return Application exit code.
   */
  int
  run(HINSTANCE hInstance,
      HINSTANCE hPrevInstance,
      LPWSTR lpCmdLine,
      int nCmdShow,
      WNDPROC wndproc);

private:
  //Customs
  Window g_window;
  Device g_device;
  SwapChain g_swapChain;
  DeviceContext g_deviceContext;
  Texture g_backBuffer;
  RenderTargetView g_renderTargetView;
  Texture g_depthStencil;
  DepthStencilView g_depthStencilView;
  Viewport g_viewport;
  ShaderProgram g_shaderProgram;
  ShaderProgram g_shaderShadow;
  BlendState g_shadowBlendState;
  DepthStencilState g_shadowDepthStencilState;

  // Camera Buffers
  Buffer m_neverChanges;
  Buffer m_changeOnResize;

  // Cube Buffers
  Buffer m_vertexBuffer;
  Buffer m_indexBuffer;
  Buffer m_changeEveryFrame;
  // Cube Shadow Buffers
  Buffer m_constShadow;

  // Plane Buffers
  Buffer m_planeVertexBuffer;
  Buffer m_planeIndexBuffer;
  Buffer m_constPlane;

  // Variable global para el constant buffer de la luz puntual
  ID3D11ShaderResourceView* g_pTextureRV = NULL;
  ID3D11SamplerState* g_pSamplerLinear = NULL;
  XMMATRIX g_World;         // Para el cubo
  XMMATRIX g_PlaneWorld;    // Para el plano
  XMMATRIX                            g_View;
  XMMATRIX                            g_Projection;

  //----- Variables agregadas para el plano y sombras -----//
  UINT                                g_planeIndexCount = 0;

  float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f };
  float blendFactor[4] = { 0.f, 0.f, 0.f, 0.f };
  MeshComponent cubeMesh;
  MeshComponent planeMesh;
  CBNeverChanges cbNeverChanges;
  CBChangeOnResize cbChangesOnResize;
  CBChangesEveryFrame cbPlane;
  CBChangesEveryFrame cb;
  CBChangesEveryFrame cbShadow;
};
