#pragma once
#include "Prerequisites.h"
#include "ECS/Component.h"

class DeviceContext;

/**
 * @class Entity
 * @brief Base class for all entities in the ECS (Entity-Component-System) architecture.
 *
 * The Entity class provides a common interface for all game or simulation objects that can
 * contain components. It defines the lifecycle methods (init, update, render, destroy) and
 * manages a collection of components. Entities can be extended to implement specific logic
 * and behavior.
 */
class Entity {
public:
  /**
   * @brief Default constructor for the Entity class.
   */
  Entity() = default;

  /**
   * @brief Virtual destructor for the Entity class.
   */
  virtual ~Entity() = default;

  /**
   * @brief Initializes the entity.
   *
   * This method should be overridden by derived classes to perform any setup required
   * before the entity is used.
   */
  virtual void init() = 0;

  /**
   * @brief Updates the entity.
   * @param deltaTime Time elapsed since the last update (in seconds).
   * @param deviceContext Reference to the device context for graphics operations.
   *
   * This method should be overridden by derived classes to update the entity's state.
   */
  virtual void update(const float deltaTime, DeviceContext& deviceContext) = 0;

  /**
   * @brief Renders the entity.
   * @param deviceContext Reference to the device context for graphics operations.
   *
   * This method should be overridden by derived classes to render the entity.
   */
  virtual void render(DeviceContext& deviceContext) = 0;

  /**
   * @brief Destroys the entity and releases resources.
   *
   * This method should be overridden by derived classes to clean up resources.
   */
  virtual void destroy() = 0;

  /**
   * @brief Adds a component to the entity.
   * @tparam T Type of the component to add (must derive from Component).
   * @param component Shared pointer to the component to be added.
   *
   * The component is stored as a base Component pointer internally.
   */
  template <typename T>
  void addComponent(EngineUtilities::TSharedPointer<T> component) {
    static_assert(std::is_base_of<Component, T>::value,
      "T must be derived from Component");
    m_components.push_back(component.template dynamic_pointer_cast<Component>());
  }

  /**
   * @brief Gets a component of the specified type.
   * @tparam T Type of the component to retrieve.
   * @return Shared pointer to the requested component, or nullptr if not found.
   *
   * Iterates through the entity's components and returns the first component
   * that matches the requested type.
   */
  template <typename T>
  EngineUtilities::TSharedPointer<T> getComponent() {
    for (auto& component : m_components) {
      EngineUtilities::TSharedPointer<T> specificComponent = component.template dynamic_pointer_cast<T>();
      if (specificComponent) {
        return specificComponent; ///< Return the component if found.
      }
    }
    return EngineUtilities::TSharedPointer<T>(); ///< Return nullptr if not found.
  }

protected:
  bool m_isActive; ///< Indicates whether the entity is active.
  int m_id; ///< Unique identifier for the entity.
  std::vector<EngineUtilities::TSharedPointer<Component>> m_components; ///< Components associated with the entity.
};
