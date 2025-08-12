#pragma once
#include "Prerequisites.h"
#include "Engine Utilities/Vectors/Vector3.h"
#include "Component.h"

/**
 * @class Transform
 * @brief Component that manages position, rotation, scale, and transformation matrix for an entity.
 *
 * The Transform component encapsulates the spatial properties of an entity, including its position,
 * rotation, and scale in 3D space. It also maintains a transformation matrix that can be used for
 * rendering or physics calculations. This component is fundamental for any object that requires
 * spatial manipulation in a scene.
 */
class Transform : public Component {
public:
  /**
   * @brief Default constructor.
   *
   * Initializes position, rotation, and scale to their default values (usually zero vectors),
   * and sets the component type to TRANSFORM.
   */
  Transform() : position(),
    rotation(),
    scale(),
    matrix(),
    Component(ComponentType::TRANSFORM) {
  }

  /**
   * @brief Initializes the Transform component.
   *
   * This method should be called before using the component to ensure all internal data
   * is set up correctly.
   */
  void init();

  /**
   * @brief Updates the state of the Transform component based on elapsed time.
   * @param deltaTime Time elapsed since the last update (in seconds).
   *
   * This method can be used to animate or otherwise modify the transform over time.
   */
  void update(float deltaTime) override;

  /**
   * @brief Renders the Transform component.
   * @param deviceContext Reference to the device context for graphics operations.
   *
   * The default implementation does nothing, as Transform is typically not directly rendered.
   */
  void render(DeviceContext& deviceContext) override {}

  /**
   * @brief Destroys the Transform component and releases resources.
   *
   * The default implementation does nothing, as Transform does not own external resources.
   */
  void destroy() {}

  /**
   * @brief Gets the current position.
   * @return Reference to the current position vector.
   */
  const EngineUtilities::Vector3& getPosition() const { return position; }

  /**
   * @brief Sets a new position.
   * @param newPos The new position vector.
   */
  void setPosition(const EngineUtilities::Vector3& newPos) { position = newPos; }

  /**
   * @brief Gets the current rotation.
   * @return Reference to the current rotation vector (in degrees or radians, depending on convention).
   */
  const EngineUtilities::Vector3& getRotation() const { return rotation; }

  /**
   * @brief Sets a new rotation.
   * @param newRot The new rotation vector.
   */
  void setRotation(const EngineUtilities::Vector3& newRot) { rotation = newRot; }

  /**
   * @brief Gets the current scale.
   * @return Reference to the current scale vector.
   */
  const EngineUtilities::Vector3& getScale() const { return scale; }

  /**
   * @brief Sets a new scale.
   * @param newScale The new scale vector.
   */
  void setScale(const EngineUtilities::Vector3& newScale) { scale = newScale; }

  /**
   * @brief Sets position, rotation, and scale in a single call.
   * @param newPos The new position vector.
   * @param newRot The new rotation vector.
   * @param newSca The new scale vector.
   *
   * This method is useful for updating all transform properties at once.
   */
  void setTransform(const EngineUtilities::Vector3& newPos,
    const EngineUtilities::Vector3& newRot,
    const EngineUtilities::Vector3& newSca);

  /**
   * @brief Translates (moves) the object by the given vector.
   * @param translation Vector representing the amount to move in each axis.
   *
   * Adds the translation vector to the current position.
   */
  void translate(const EngineUtilities::Vector3& translation);

private:
  EngineUtilities::Vector3 position;  ///< Position of the object in world space.
  EngineUtilities::Vector3 rotation;  ///< Rotation of the object (typically in degrees or radians).
  EngineUtilities::Vector3 scale;     ///< Scale of the object.

public:
  XMMATRIX matrix;    ///< Transformation matrix representing the combined position, rotation, and scale.
};
