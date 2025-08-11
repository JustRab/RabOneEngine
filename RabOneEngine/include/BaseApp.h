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
#include "ECS/Actor.h"
#include "SamplerState.h"

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

public:
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

  ///**
  // * @brief Blend state for shadow rendering.
  // */
  //BlendState g_shadowBlendState;

  ///**
  // * @brief Depth-stencil state for shadow rendering.
  // */
  //DepthStencilState g_shadowDepthStencilState;

  /**
   * @brief User interface manager.
   */
  UserInterface g_userInterface;

  /**
   * @brief Model loader for loading 3D models.
   */
  ModelLoader m_loader;

  /**
   * @brief Sampler state for texture sampling.
   */
  SamplerState g_samplerState;

  // --- Camera Buffers ---

  /**
   * @brief Constant buffer for data that never changes.
   */
  Buffer m_neverChanges;

  /**
   * @brief Constant buffer for data that changes on window resize.
   */
  Buffer m_changeOnResize;

  // --- Texture and Sampler Resources ---

  Texture g_koroTexture; ///< Texture for the Koro model.
  Texture g_planeTexture; ///< Texture for the plane.

  // --- Transformation Matrices ---

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

  // --- Mesh Components ---

  /**
   * @brief Mesh component for the cube.
   */
  MeshComponent cubeMesh;

  /**
   * @brief Mesh component for the plane.
   */
  MeshComponent planeMesh;

  /**
   * @brief Mesh component for the model.
   */
  MeshComponent koroMesh;

  // --- Constant Buffer Structures ---

  /**
   * @brief Constant buffer for data that never changes.
   */
  CBNeverChanges cbNeverChanges;

  /**
   * @brief Constant buffer for data that changes on window resize.
   */
  CBChangeOnResize cbChangesOnResize;

  EngineUtilities::TSharedPointer<Actor> g_AKoro; ///< Shared pointer to the Koro actor in the scene.
  EngineUtilities::TSharedPointer<Actor> g_APlane; ///< Shared pointer to the plane actor in the scene.
  std::vector<EngineUtilities::TSharedPointer<Actor>> g_actors; ///< Vector of actors in the scene.

  XMFLOAT4 g_LightPos; ///< Posición de la luz(2.0f, 4.0f, -2.0f, 1.0f)
};
