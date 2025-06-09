#pragma once
#include "Prerequisites.h"

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
  BaseApp();
  /**
   * @brief Destroys the BaseApp instance and releases any held resources.
   */
  ~BaseApp();

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

};
