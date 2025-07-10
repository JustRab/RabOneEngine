#pragma once

//--------------------------------------------------------------------------------------
// Standard Library Includes
//--------------------------------------------------------------------------------------
#include <string>
#include <sstream>
#include <vector>
#include <windows.h>
#include <xnamath.h>
#include <thread>

//--------------------------------------------------------------------------------------
// DirectX Library Includes
//--------------------------------------------------------------------------------------
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include "Resource.h"
//#include "resource.h"

//--------------------------------------------------------------------------------------
// ImGui Library Includes
//--------------------------------------------------------------------------------------
#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_internal.h>
#include "imgui_impl_win32.h"


//--------------------------------------------------------------------------------------
// MACROS
//--------------------------------------------------------------------------------------

/**
 * @brief Safely releases a COM object and sets its pointer to nullptr.
 * @param x Pointer to the COM object to release.
 */
#define SAFE_RELEASE(x) if(x != nullptr) x->Release(); x = nullptr;

/**
 * @brief Prints a debug message indicating the creation of a resource, including the class name, method, and resource state.
 * @param classObj Name of the class.
 * @param method Name of the method.
 * @param state State or description of the resource.
 */
#define MESSAGE( classObj, method, state )   \
{                                            \
   std::wostringstream os_;                  \
   os_ << classObj << "::" << method << " : " << "[CREATION OF RESOURCE " << ": " << state << "] \n"; \
   OutputDebugStringW( os_.str().c_str() );  \
}

/**
 * @brief Prints a debug error message with the class name, method, and error description.
 * @param classObj Name of the class.
 * @param method Name of the method.
 * @param errorMSG Error message or description.
 */
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
/**
 * @struct SimpleVertex
 * @brief Represents a simple vertex with position and texture coordinates.
 */
struct
  SimpleVertex {
  XMFLOAT3 Pos; ///< Position of the vertex.
  XMFLOAT2 Tex; ///< Texture coordinates of the vertex.
};

/**
 * @struct CBNeverChanges
 * @brief Constant buffer structure for a "view" matrix that does not change.
 */
struct
  CBNeverChanges {
  XMMATRIX mView; ///< View matrix.
};

/**
 * @struct CBChangeOnResize
 * @brief Constant buffer structure for a "projection" matrix that changes when the window is resized.
 */
struct
  CBChangeOnResize {
  XMMATRIX mProjection; ///< Projection matrix.
};

/**
 * @struct CBChangesEveryFrame
 * @brief Constant buffer structure for "world" matrix and mesh color that change every frame.
 */
struct
  CBChangesEveryFrame {
  XMMATRIX mWorld;      ///< World matrix.
  XMFLOAT4 vMeshColor;  ///< Mesh color.
};

/**
 * @enum ExtensionType
 * @brief Enumeration for supported file extension types.
 */
enum
  ExtensionType {
  DDS = 0, ///< DirectDraw Surface format.
  PNG = 1, ///< Portable Network Graphics format.
  JPG = 2  ///< JPEG image format.
};

enum
ShaderType {
  VERTEX_SHADER = 0, ///< Vertex shader type.
  PIXEL_SHADER = 1,  ///< Pixel shader type.
};