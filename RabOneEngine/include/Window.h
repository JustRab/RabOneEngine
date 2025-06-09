#pragma once
#include "Prerequisites.h"

/**
 * @class Window
 * @brief Encapsulates a Win32 window, providing initialization, update, render, and destruction functionality.
 *
 * The Window class manages the lifecycle and state of a Win32 window, including creation, message handling,
 * rendering, and cleanup. It stores window handles, dimensions, and other relevant data.
 */
class
Window {
public:

  /**
   * @brief Default constructor and destructor.
   */
  Window() = default;
  ~Window() = default;

  /**
   * @brief Initializes the window with the given instance and command show parameters.
   * @param hInstance The handle to the application instance.
   * @param nCmdShow The command to show the window (e.g., SW_SHOW).
   * @param wndproc The window procedure function pointer.
   * @return HRESULT indicating success or failure.
   */
  HRESULT 
  init(HINSTANCE hInstance, int nCmdShow, WNDPROC wndproc);

  /**
   * @brief Updates the window state and handles any necessary processing.
   *
   * Typically called once per frame to process window messages and update internal state.
   */
  void
  update();

  /**
   * @brief Renders the window content, typically called in the main loop.
   *
   * Override or extend this method to implement custom rendering logic.
   */
  void
  render();

  /**
   * @brief Destroys the window and cleans up resources.
   *
   * Should be called before application exit to release window resources.
   */
  void
  destroy();

public:
  /**
   * @brief Handle to the window.
   */
  HWND m_hWnd = nullptr;
  /**
   * @brief Width of the window in pixels.
   */
  unsigned int m_width;
  /**
   * @brief Height of the window in pixels.
   */
  unsigned int m_height;

private:
  /**
   * @brief Handle to the application instance.
   */
  HINSTANCE m_hInst = nullptr;
  /**
   * @brief Rectangle describing the window's position and size.
   */
  RECT m_rect;
  /**
   * @brief Name of the window (used as the window title).
   */
  std::string m_windowName = "RabOneEngine";
};
