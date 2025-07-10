#pragma once
#include "Prerequisites.h"

class Device;
class DeviceContext;

/**
 * @class InputLayout
 * @brief Encapsulates a Direct3D input layout object and provides methods for initialization, binding, and cleanup.
 *
 * The InputLayout class manages the creation, usage, and destruction of a Direct3D input layout,
 * which defines how vertex buffer data is interpreted and fed into the vertex shader stage.
 */
class 
InputLayout {
public:
  /**
   * @brief Default constructor.
   */
  InputLayout() = default;

  /**
   * @brief Destructor.
   */
  ~InputLayout() = default;

  /**
   * @brief Initializes the input layout using the provided device, input element descriptions, and vertex shader bytecode.
   * @param device Reference to the Direct3D device used to create the input layout.
   * @param Layout Reference to a vector of D3D11_INPUT_ELEMENT_DESC structures describing the input layout.
   * @param VertexShaderData Pointer to the compiled vertex shader bytecode (ID3DBlob).
   * @return HRESULT indicating success or failure of the initialization.
   */
  HRESULT 
  init(Device& device,
       std::vector<D3D11_INPUT_ELEMENT_DESC>& Layout,
       ID3DBlob* VertexShaderData);

  /**
   * @brief Updates the input layout. (No-op in this implementation.)
   */
  void 
  update();

  /**
   * @brief Binds the input layout to the input assembler stage for rendering.
   * @param deviceContext Reference to the device context used for rendering.
   */
  void 
  render(DeviceContext& deviceContext);

  /**
   * @brief Releases the input layout and frees associated resources.
   */
  void 
  destroy();

public:
  /**
   * @brief Pointer to the underlying Direct3D input layout object.
   */
  ID3D11InputLayout* m_inputLayout = nullptr;
};
