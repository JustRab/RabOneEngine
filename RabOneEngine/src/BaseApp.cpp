#include "BaseApp.h"

// Inicializa
HRESULT 
BaseApp::init() {
  return E_NOTIMPL;
}

// Actualiza el estado de la aplicación. Debe ser sobreescrito por clases derivadas.
void 
BaseApp::update() {
}

// Renderiza la escena o interfaz de la aplicación.
void 
BaseApp::render() {
}

// Libera los recursos utilizados por la aplicación. 
void 
BaseApp::destroy() {
}

// Ejecuta la aplicación, configurando el entorno y el bucle principal.
int 
BaseApp::run(HINSTANCE hInstance0,
             HINSTANCE hPrevInstance,
             LPWSTR lpCmdLine,
             int nCmdShow, WNDPROC wndproc) {
  return 0;
}
