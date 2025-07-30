#pragma once

#include "Prerequisites.h"
class DeviceContext;

class
  Component {
public:
  /**
  * @brief Default constructor for the Component class.
  */
  Component() = default;

  /**
  * @brief Contructor with component type.
  * @param type The type of the component.
  */
  Component(const ComponentType type) : m_type(type) {}

  /**
  * @brief Virtual destructor for the Component class.
  */
  virtual
  ~Component() = default;

  virtual void
  init() = 0; ///< Initialize the component.

  /**
  * @brief Virtual method to update the component.
  * @param deltaTime Time elapsed since the last update.
  */
  virtual void
  update(const float deltaTime) = 0;

  /**
  * @brief Virtual method to render the component.
  * @param deviceContext The device context used for rendering and graphic operations.
  */
  virtual void
  render(DeviceContext& deviceContext) = 0;

  virtual void
  destroy() = 0; ///< Destroy the component and release resources.
  /**
  * @brief Get the type of the component.
  * @return The type of the component.
  */
  ComponentType
  getType() const { return m_type; }

protected:
  ComponentType m_type; ///< Type of the component.
};