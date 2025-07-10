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
#include "UserInterface.h"
#include "ModelLoader.h"

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
  // --- Core Engine Components ---

  /**
   * @brief Main application window.
   */
  Window g_window;

  /**
   * @brief Direct3D device for resource creation and management.
   */
  Device g_device;

  /**
   * @brief Swap chain for presenting rendered frames.
   */
  SwapChain g_swapChain;

  /**
   * @brief Device context for issuing rendering commands.
   */
  DeviceContext g_deviceContext;

  /**
   * @brief Back buffer texture.
   */
  Texture g_backBuffer;

  /**
   * @brief Render target view for the back buffer.
   */
  RenderTargetView g_renderTargetView;

  /**
   * @brief Depth-stencil texture.
   */
  Texture g_depthStencil;

  /**
   * @brief Depth-stencil view.
   */
  DepthStencilView g_depthStencilView;

  /**
   * @brief Viewport configuration.
   */
  Viewport g_viewport;

  /**
   * @brief Main shader program.
   */
  ShaderProgram g_shaderProgram;

  /**
   * @brief Shader program used for shadow rendering.
   */
  ShaderProgram g_shaderShadow;

  /**
   * @brief Blend state for shadow rendering.
   */
  BlendState g_shadowBlendState;

  /**
   * @brief Depth-stencil state for shadow rendering.
   */
  DepthStencilState g_shadowDepthStencilState;

  /**
   * @brief User interface manager.
   */
  UserInterface g_userInterface;

  /**
   * @brief Model loader for loading 3D models.
   */
  ModelLoader m_loader;

  // --- Camera Buffers ---

  /**
   * @brief Constant buffer for data that never changes.
   */
  Buffer m_neverChanges;

  /**
   * @brief Constant buffer for data that changes on window resize.
   */
  Buffer m_changeOnResize;

  // --- Cube Buffers ---

  /**
   * @brief Vertex buffer for the cube.
   */
  Buffer m_vertexBuffer;

  /**
   * @brief Index buffer for the cube.
   */
  Buffer m_indexBuffer;

  /**
   * @brief Constant buffer for data that changes every frame (cube).
   */
  Buffer m_changeEveryFrame;

  // --- Cube Shadow Buffers ---

  /**
   * @brief Constant buffer for shadow rendering (cube).
   */
  Buffer m_constShadow;

  // --- Plane Buffers ---

  /**
   * @brief Vertex buffer for the plane.
   */
  Buffer m_planeVertexBuffer;

  /**
   * @brief Index buffer for the plane.
   */
  Buffer m_planeIndexBuffer;

  /**
   * @brief Constant buffer for the plane.
   */
  Buffer m_constPlane;

  // --- Texture and Sampler Resources ---

  /**
   * @brief Shader resource view for the cube texture.
   */
  ID3D11ShaderResourceView* g_pTextureRV = NULL;

  /**
   * @brief Sampler state for the cube texture.
   */
  ID3D11SamplerState* g_pSamplerLinear = NULL;

  /**
   * @brief Shader resource view for the plane texture.
   */
  ID3D11ShaderResourceView* g_pPlaneTextureRV = NULL;

  /**
   * @brief Sampler state for the plane texture.
   */
  ID3D11SamplerState* g_pPlaneSamplerLinear = NULL;

  // --- Transformation Matrices ---

  /**
   * @brief World matrix for the cube.
   */
  XMMATRIX g_World;

  /**
   * @brief World matrix for the plane.
   */
  XMMATRIX g_PlaneWorld;

  /**
   * @brief View matrix.
   */
  XMMATRIX g_View;

  /**
   * @brief Projection matrix.
   */
  XMMATRIX g_Projection;

  // --- Plane and Shadow Variables ---

  /**
   * @brief Index count for the plane mesh.
   */
  UINT g_planeIndexCount = 0;

  // --- Rendering State ---

  /**
   * @brief Color used to clear the render target.
   */
  float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f };

  /**
   * @brief Blend factor for blending operations.
   */
  float blendFactor[4] = { 0.f, 0.f, 0.f, 0.f };

  // --- Mesh Components ---

  /**
   * @brief Mesh component for the cube.
   */
  MeshComponent cubeMesh;

  /**
   * @brief Mesh component for the plane.
   */
  MeshComponent planeMesh;

  // --- Constant Buffer Structures ---

  /**
   * @brief Constant buffer for data that never changes.
   */
  CBNeverChanges cbNeverChanges;

  /**
   * @brief Constant buffer for data that changes on window resize.
   */
  CBChangeOnResize cbChangesOnResize;

  /**
   * @brief Constant buffer for the plane (per-frame changes).
   */
  CBChangesEveryFrame cbPlane;

  /**
   * @brief Constant buffer for the cube (per-frame changes).
   */
  CBChangesEveryFrame cb;

  /**
   * @brief Constant buffer for shadow rendering (per-frame changes).
   */
  CBChangesEveryFrame cbShadow;

public:
  /**
   * @brief Position of the main object or camera in world space.
   */
  XMFLOAT3 position;

  /**
   * @brief Rotation of the main object or camera in world space.
   */
  XMFLOAT3 rotation;

  /**
   * @brief Scale of the main object or camera in world space.
   */
  XMFLOAT3 scale;
};
