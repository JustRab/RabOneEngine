#pragma once
#include "Prerequisites.h"
#include "InputLayout.h"

class Device;
class DeviceContext;

/**
 * @class ShaderProgram
 * @brief Encapsulates a Direct3D shader program, including vertex and pixel shaders, input layout, and related operations.
 *
 * The ShaderProgram class manages the creation, compilation, and binding of vertex and pixel shaders,
 * as well as the associated input layout. It provides methods for initialization, updating, rendering,
 * and cleanup of shader resources.
 */
class ShaderProgram {
public:
  /**
   * @brief Default constructor.
   */
  ShaderProgram() = default;

  /**
   * @brief Destructor.
   */
  ~ShaderProgram() = default;

  /**
   * @brief Initializes the shader program with the specified shader file and input layout.
   * @param device Reference to the Direct3D device used for resource creation.
   * @param fileName Path to the shader file.
   * @param Layout Vector of input element descriptions for the input layout.
   * @return HRESULT indicating success or failure of the initialization.
   */
  HRESULT 
  init(Device& device,
       const std::string& fileName,
       std::vector<D3D11_INPUT_ELEMENT_DESC> Layout);

  /**
   * @brief Updates the shader program state. (No-op in this implementation.)
   */
  void update();

  /**
   * @brief Binds the shader program and input layout to the device context for rendering.
   * @param deviceContext Reference to the device context used for rendering.
   */
  void 
  render(DeviceContext& deviceContext);

  /**
   * @brief Binds the specified shader type to the device context for rendering.
   * @param deviceContext Reference to the device context used for rendering.
   * @param type Shader type to bind (vertex or pixel shader).
   */
  void
  render(DeviceContext& deviceContext,
         ShaderType type);

  /**
   * @brief Releases all shader resources and cleans up the shader program.
   */
  void destroy();

  /**
   * @brief Creates the input layout for the shader program.
   * @param device Reference to the Direct3D device used for resource creation.
   * @param Layout Vector of input element descriptions.
   * @return HRESULT indicating success or failure of the input layout creation.
   */
  HRESULT 
  CreateInputLayout(Device& device,
                    std::vector<D3D11_INPUT_ELEMENT_DESC> Layout);

  /**
   * @brief Creates the specified shader type from the loaded shader file.
   * @param device Reference to the Direct3D device used for resource creation.
   * @param type Shader type to create (vertex or pixel shader).
   * @return HRESULT indicating success or failure of the shader creation.
   */
  HRESULT 
  CreateShader(Device& device,
               ShaderType type);

  /**
   * @brief Creates the specified shader type from the given shader file.
   * @param device Reference to the Direct3D device used for resource creation.
   * @param type Shader type to create (vertex or pixel shader).
   * @param fileName Path to the shader file.
   * @return HRESULT indicating success or failure of the shader creation.
   */
  HRESULT CreateShader(Device& device,
                       ShaderType type,
                       const std::string& fileName);

  /**
   * @brief Compiles a shader from file.
   * @param szFileName Path to the shader file.
   * @param szEntryPoint Entry point function name.
   * @param szShaderModel Shader model to use for compilation.
   * @param ppBlobOut Output pointer for the compiled shader blob.
   * @return HRESULT indicating success or failure of the compilation.
   */
  HRESULT 
  CompileShaderFromFile(char* szFileName,
                        LPCSTR szEntryPoint,
                        LPCSTR szShaderModel,
                        ID3DBlob** ppBlobOut);

public:
  ID3D11VertexShader* m_VertexShader = nullptr; ///< Pointer to the vertex shader object.
  ID3D11PixelShader* m_PixelShader = nullptr;   ///< Pointer to the pixel shader object.
  InputLayout m_inputLayout;                    ///< Input layout associated with the shader program.

private:
  std::string m_shaderFileName;                 ///< Path to the shader file.
  ID3DBlob* m_vertexShaderData = nullptr;       ///< Compiled vertex shader data.
  ID3DBlob* m_pixelShaderData = nullptr;        ///< Compiled pixel shader data.
};
