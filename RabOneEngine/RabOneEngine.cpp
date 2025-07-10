#include "BaseApp.h"
#include "UserInterface.h"

//----------------------------------------------------------------------------------------
// Variables globales
//----------------------------------------------------------------------------------------
BaseApp g_baseApp;

IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//--------------------------------------------------------------------------------------
// Función de mensaje de la ventana
//--------------------------------------------------------------------------------------
LRESULT CALLBACK 
WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
  PAINTSTRUCT ps;
  HDC hdc;

  if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
    return true;

  switch (message)
  {
  case WM_PAINT:
    hdc = BeginPaint(hWnd, &ps);
    EndPaint(hWnd, &ps);
    break;

  case WM_DESTROY:
    PostQuitMessage(0);
    break;

  default:
    return DefWindowProc(hWnd, message, wParam, lParam);
  }

  return 0;
}

//--------------------------------------------------------------------------------------
// Punto de entrada del programa. Inicializa todo y entra en el bucle de mensajes.
//--------------------------------------------------------------------------------------
int WINAPI
wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
  return g_baseApp.run(hInstance, hPrevInstance, lpCmdLine, nCmdShow, WndProc);
}