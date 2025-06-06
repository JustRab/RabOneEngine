#pragma once

// Librerias STD
#include <string>
#include <sstream>
#include <vector>
#include <windows.h>
#include <xnamath.h>
#include <thread>

// Librerias de DirectX
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include "Resource.h"
//#include "resource.h"

//--------------------------------------------------------------------------------------
// MACROS
//--------------------------------------------------------------------------------------

// Libera de manera segura un objeto COM.
#define SAFE_RELEASE(x) if(x != nullptr) x->Release(); x = nullptr;

// Imprime un mensaje de depuración indicando la creación de un recurso; con el nombre de la clase, método y estado del recurso.
#define MESSAGE( classObj, method, state )   \
{                                            \
   std::wostringstream os_;                  \
   os_ << classObj << "::" << method << " : " << "[CREATION OF RESOURCE " << ": " << state << "] \n"; \
   OutputDebugStringW( os_.str().c_str() );  \
}

// Imprime un mensaje de depuración de tipo "error" con el nombre de la clase, método y estado del recurso.
#define ERROR(classObj, method, errorMSG)                     \
{                                                             \
    try {                                                     \
        std::wostringstream os_;                              \
        os_ << L"ERROR : " << classObj << L"::" << method     \
            << L" : " << errorMSG << L"\n";                   \
        OutputDebugStringW(os_.str().c_str());                \
    } catch (...) {                                           \
        OutputDebugStringW(L"Failed to log error message.\n");\
    }                                                         \
}

//--------------------------------------------------------------------------------------
// Estructuras
//--------------------------------------------------------------------------------------
// Representa un vértice simple con posición y coordenadas de textura
struct 
SimpleVertex {
    XMFLOAT3 Pos;
    XMFLOAT2 Tex;
};

// Estructura de un buffer constante para matrices "view" que no cambian.
struct
CBNeverChanges {
    XMMATRIX mView;
};

// Estructura de un buffer constante para matrices "projection" que cambian al redimensionar la ventana.
struct 
CBChangeOnResize {
    XMMATRIX mProjection;
};

// Estructura de un buffer constante para matrices "world" y el color del mesh que cambian cada frame.
struct 
CBChangesEveryFrame {
    XMMATRIX mWorld;
    XMFLOAT4 vMeshColor;
};

// Enumeración para tipos de extensiones de archivos soportados
enum 
ExtensionType {
  DDS = 0,
	PNG = 1,
	JPG = 2
};