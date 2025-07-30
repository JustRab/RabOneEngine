#pragma once
#include "Prerequisites.h"
#include "ECS/Component.h"

class DeviceContext;

class Entity {
public:
  /**
   * @brief Default constructor for the Entity class.
   */
  Entity() = default;

  /**
   * @brief Virtual destructor for the Entity class.
   */
  virtual
    ~Entity() = default;
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
  * @brief Adds a component to the entity.
  * @tparam T Component type to be added.
  * @param component Shared pointer to the component to be added.
  */
  template <typename T> void
    addComponent(EngineUtilities::TSharedPointer<T> component) {
    static_assert(std::is_base_of<Component, T>::value,
                  "T must be derived from Component");
    m_components.push_back(component.template dynamic_pointer_cast<Component>());
  }

  /**
  * @brief Obtiene un componente del tipo solicitado.
  * @tparam T Tipo del componente a obtener.
  * @return Shared pointer al componente solicitado, o nullptr si no existe.
  */
  template <typename T>
  EngineUtilities::TSharedPointer<T> 
  getComponent() {
    for (auto& component : m_components) {
      EngineUtilities::TSharedPointer<T> specificComponent = component.template dynamic_pointer_cast<T>();
      if (specificComponent) {
        return specificComponent; ///< Return the component if found.
      }
    }
    return EngineUtilities::TSharedPointer<T>(); ///< Return nullptr if not found.
  }
private:
protected:
  bool m_isActive;
  int m_id;
  std::vector<EngineUtilities::TSharedPointer<Component>> m_components; ///< Components associated with the entity.
};
