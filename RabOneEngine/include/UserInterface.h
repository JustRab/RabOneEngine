#pragma once
#include "Prerequisites.h"

// Forward Declarations
class Window;
class Device;
class DeviceContext;
class BaseApp;

class
UserInterface {
public:
  /**
   * @brief Constructs a new UserInterface instance.
   */
  UserInterface() = default;
  /**
   * @brief Destroys the UserInterface instance and releases any held resources.
   */
  ~UserInterface() = default;
  /**
   * @brief Initializes the user interface by setting up ImGui.
   * @param window Pointer to the application window.
   * @param device Pointer to the Direct3D device.
   * @param deviceContext Pointer to the Direct3D device context.
   */
  void
  init(void* window,
       ID3D11Device* device,
       ID3D11DeviceContext* deviceContext);

  /**
  * @brief Updates the user interface each frame.
  */
  void
  update();
  /**
   * @brief Renders the user interface each frame.
   */
  void
  render();
  /**
   * @brief Cleans up and releases ImGui resources.
   */
  void
  destroy();
  /**
     * @brief Set the style and colors of the UI using ImGUI
     */
  void
  setupGUIStyle();

  /**
   * @brief Method place holder, contains the content information to be displayed in the UI of the ImGui tab
   */
  void
  GUITab(const std::string& tabName);

  /**
   * @brief Place holder method, contains the user interface components to be displayed in the ImGui tab
   */
  void
  TransformGUI(BaseApp& g_bApp);

  /**
   * @brief Allows you to manipulate three float values in the GUI
   * @param label Label to be displayed next to the control.
   * @param values Pointer to the two floating values (X, Y, Z) to be manipulated.
   * @param resetValues Default value to reset the values.
   * @param columnWidth Width of the column to arrange the interface elements.
   */
  void
    vec3Control(const std::string& label,
      float* values,
      float resetValues = 0.0f,
      float columnWidth = 100.0f);

private:

};