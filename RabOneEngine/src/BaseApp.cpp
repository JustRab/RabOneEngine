#include "BaseApp.h"

// Inicializa
HRESULT 
BaseApp::init() {
  return E_NOTIMPL;
}

// Actualiza el estado de la aplicaci�n. Debe ser sobreescrito por clases derivadas.
void 
BaseApp::update() {
}

// Renderiza la escena o interfaz de la aplicaci�n.
void 
BaseApp::render() {
}

// Libera los recursos utilizados por la aplicaci�n. 
void 
BaseApp::destroy() {
}

// Ejecuta la aplicaci�n, configurando el entorno y el bucle principal.
int 
BaseApp::run(HINSTANCE hInstance0,
             HINSTANCE hPrevInstance,
             LPWSTR lpCmdLine,
             int nCmdShow, WNDPROC wndproc) {
  return 0;
}
