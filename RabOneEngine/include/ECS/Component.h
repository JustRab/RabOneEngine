#pragma once

#include "Prerequisites.h"
class DeviceContext;

/**
 * @class Component
 * @brief Abstract base class for all components in the ECS (Entity-Component-System) architecture.
 *
 * The Component class defines the interface and common functionality for all components
 * that can be attached to entities. Components encapsulate specific behaviors or data,
 * and are managed by entities. All derived components must implement the lifecycle methods.
 */
class Component {
public:
  /**
   * @brief Default constructor for the Component class.
   */
  Component() = default;

  /**
   * @brief Constructor with component type.
   * @param type The type of the component.
   */
  Component(const ComponentType type) : m_type(type) {}

  /**
   * @brief Virtual destructor for the Component class.
   */
  virtual ~Component() = default;

  /**
   * @brief Initializes the component.
   *
   * This method should be overridden by derived classes to perform any setup required
   * before the component is used.
   */
  virtual void init() = 0;

  /**
   * @brief Updates the component.
   * @param deltaTime Time elapsed since the last update (in seconds).
   *
   * This method should be overridden by derived classes to update the component's state.
   */
  virtual void update(const float deltaTime) = 0;

  /**
   * @brief Renders the component.
   * @param deviceContext Reference to the device context for graphics operations.
   *
   * This method should be overridden by derived classes to render the component.
   */
  virtual void render(DeviceContext& deviceContext) = 0;

  /**
   * @brief Destroys the component and releases resources.
   *
   * This method should be overridden by derived classes to clean up resources.
   */
  virtual void destroy() = 0;

  /**
   * @brief Gets the type of the component.
   * @return The type of the component.
   */
  ComponentType getType() const { return m_type; }

protected:
  ComponentType m_type; ///< Type of the component.
};
