#include "UserInterface.h"
#include "Window.h"
#include "Device.h"
#include "DeviceContext.h"
#include "BaseApp.h"

void
UserInterface::init(void* window,
  ID3D11Device* device,
  ID3D11DeviceContext* deviceContext) {
  IMGUI_CHECKVERSION(); // Check ImGUI version
  ImGui::CreateContext(); // Initialize the context
  ImGuiIO& io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

  // Setup GUI Style
  setupGUIStyle();

  // / When viewports are enabled we tweak WindowRounding/WindoBg so platform windows can look identical to regular ones.
  ImGuiStyle& style = ImGui::GetStyle();
  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
  {
    style.WindowRounding = 0.0f;
    style.Colors[ImGuiCol_WindowBg].w = 1.0f;
  }

  // Setup Platform and Renderer bindings
  ImGui_ImplWin32_Init(window);
  ImGui_ImplDX11_Init(device, deviceContext);

}

void
UserInterface::update() {
  // Start the Dear ImGui frame
  ImGui_ImplDX11_NewFrame();
  ImGui_ImplWin32_NewFrame();
  ImGui::NewFrame();
}

void
UserInterface::render() {
  ImGui::Render();
  ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
  ImGuiIO& io = ImGui::GetIO();

  // Update and Render additional Platform Windows
  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
  {
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault(); // Update default platform for Windows
  }
}

void
UserInterface::destroy() {
  // Cleanup
  ImGui_ImplDX11_Shutdown();
  ImGui_ImplWin32_Shutdown();
  ImGui::DestroyContext();
}

void
UserInterface::setupGUIStyle() {
  ImGuiStyle& style = ImGui::GetStyle();
  ImVec4* colors = style.Colors;

  // Paleta basada en verde lima, naranja y blanco brillante
  colors[ImGuiCol_Text] = ImVec4(0.95f, 1.00f, 0.95f, 1.00f);
  colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.15f, 0.10f, 1.00f); // Verde oscuro
  colors[ImGuiCol_ChildBg] = ImVec4(0.12f, 0.18f, 0.12f, 1.00f);
  colors[ImGuiCol_Border] = ImVec4(0.30f, 0.60f, 0.30f, 0.60f); // Verde claro
  colors[ImGuiCol_FrameBg] = ImVec4(0.16f, 0.26f, 0.16f, 1.00f);
  colors[ImGuiCol_FrameBgHovered] = ImVec4(0.20f, 0.35f, 0.20f, 1.00f);
  colors[ImGuiCol_FrameBgActive] = ImVec4(0.25f, 0.40f, 0.25f, 1.00f);
  colors[ImGuiCol_TitleBg] = ImVec4(0.12f, 0.20f, 0.12f, 1.00f);
  colors[ImGuiCol_TitleBgActive] = ImVec4(0.20f, 0.35f, 0.20f, 1.00f);

  // Botones y elementos activos en naranja
  colors[ImGuiCol_Button] = ImVec4(1.00f, 0.60f, 0.10f, 1.00f); // Naranja
  colors[ImGuiCol_ButtonHovered] = ImVec4(1.00f, 0.70f, 0.20f, 1.00f);
  colors[ImGuiCol_ButtonActive] = ImVec4(1.00f, 0.80f, 0.30f, 1.00f);

  colors[ImGuiCol_CheckMark] = ImVec4(1.00f, 0.80f, 0.30f, 1.00f);
  colors[ImGuiCol_SliderGrab] = ImVec4(0.60f, 1.00f, 0.30f, 1.00f);
  colors[ImGuiCol_SliderGrabActive] = ImVec4(0.70f, 1.00f, 0.40f, 1.00f);

  colors[ImGuiCol_Header] = ImVec4(0.30f, 0.80f, 0.30f, 0.70f);
  colors[ImGuiCol_HeaderHovered] = ImVec4(0.40f, 0.90f, 0.40f, 0.80f);
  colors[ImGuiCol_HeaderActive] = ImVec4(0.50f, 1.00f, 0.50f, 1.00f);

  colors[ImGuiCol_Separator] = ImVec4(0.40f, 0.80f, 0.40f, 0.50f);
  colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 0.50f, 0.00f, 0.40f);
  colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.00f, 0.65f, 0.20f, 0.70f);
  colors[ImGuiCol_ResizeGripActive] = ImVec4(1.00f, 0.80f, 0.40f, 1.00f);

  // Tabs
  colors[ImGuiCol_Tab] = ImVec4(0.18f, 0.28f, 0.18f, 0.80f);  // Verde oscuro translúcido
  colors[ImGuiCol_TabHovered] = ImVec4(1.00f, 0.65f, 0.10f, 0.85f);  // Naranja brillante
  colors[ImGuiCol_TabActive] = ImVec4(1.00f, 0.80f, 0.30f, 1.00f);  // Naranja más clara
  colors[ImGuiCol_TabUnfocused] = ImVec4(0.10f, 0.18f, 0.10f, 0.60f);  // Más apagado
  colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.24f, 0.36f, 0.24f, 0.85f);  // Verde con brillo tenue

  // Estilo visual
  style.WindowRounding = 10.0f;
  style.FrameRounding = 8.0f;
  style.GrabRounding = 8.0f;
  style.ScrollbarRounding = 6.0f;

  style.WindowPadding = ImVec2(12, 12);
  style.FramePadding = ImVec2(8, 6);
  style.ItemSpacing = ImVec2(10, 8);
  style.ScrollbarSize = 16.0f;
}

void
UserInterface::GUITab(const std::string& tabName) {
  ImGui::Begin(tabName.c_str());
  ImGui::End();
}

void
UserInterface::TransformGUI(BaseApp& g_bApp) {

  ImGui::Begin("Transform");

  // Access the first actor's transform component for demonstration
  // You may want to modify this to handle multiple actors or a selected actor
  if (!g_bApp.g_actors.empty() && !g_bApp.g_actors[0].isNull()) {
    auto transform = g_bApp.g_actors[0]->getComponent<Transform>();
    if (transform) {
      // Get current values
      EngineUtilities::Vector3 position = transform->getPosition();
      EngineUtilities::Vector3 rotation = transform->getRotation();
      EngineUtilities::Vector3 scale = transform->getScale();

      // Create ImGui controls
      ImGui::DragFloat3("Position", &position.x, 0.1f);
      ImGui::DragFloat3("Rotation", &rotation.x, 0.1f);
      ImGui::DragFloat3("Scale", &scale.x, 0.1f);

      // Update the transform component with new values
      transform->setPosition(position);
      transform->setRotation(rotation);
      transform->setScale(scale);
    }
  }
  else {
    ImGui::Text("No actors available");
  }

  ImGui::End();
}

void
UserInterface::vec3Control(const std::string& label,
                           float* values,
                           float resetValues,
                           float columnWidth) {
  ImGuiIO& io = ImGui::GetIO();
  auto boldFont = io.Fonts->Fonts[0];

  ImGui::PushID(label.c_str());

  ImGui::Columns(2);
  ImGui::SetColumnWidth(0, columnWidth);
  ImGui::Text(label.c_str());
  ImGui::NextColumn();

  ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
  ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

  float lineHeight = ImGui::GetFontSize() + ImGui::GetStyle().FramePadding.y * 2.0f;
  ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

  ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
  ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
  ImGui::PushFont(boldFont);
  if (ImGui::Button("X", buttonSize)) values[0] = resetValues;
  ImGui::PopFont();
  ImGui::PopStyleColor(3);

  ImGui::SameLine();
  ImGui::DragFloat("##X", &values[0], 0.1f, 0.0f, 0.0f, "%.2f");
  ImGui::PopItemWidth();
  ImGui::SameLine();

  ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
  ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
  ImGui::PushFont(boldFont);
  if (ImGui::Button("Y", buttonSize)) values[1] = resetValues;
  ImGui::PopFont();
  ImGui::PopStyleColor(3);

  ImGui::SameLine();
  ImGui::DragFloat("##Y", &values[1], 0.1f, 0.0f, 0.0f, "%.2f");
  ImGui::PopItemWidth();
  ImGui::SameLine();

  ImGui::PopStyleVar();
  ImGui::Columns(1);

  ImGui::PopID();
}