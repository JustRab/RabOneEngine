#pragma once
#include "Prerequisites.h"
#include "ECS/Component.h"

class DeviceContext;

/**
 * @class MeshComponent
 * @brief Represents a mesh component containing vertex and index data for rendering.
 *
 * The MeshComponent class encapsulates the data and basic operations for a renderable mesh,
 * including its name, vertex buffer, index buffer, and counts. It provides methods for updating
 * and rendering the mesh using a Direct3D device context.
 */
class 
MeshComponent : public Component {
public:
  /**
   * @brief Constructs a new MeshComponent instance with zeroed vertex and index counts.
   */
  MeshComponent() : m_numVertex(0), m_numIndex(0), Component(ComponentType::MESH) {}

  /**
   * @brief Virtual destructor.
   */
  virtual ~MeshComponent() = default;

  void
    init() override {};

  /**
   * @brief Updates the mesh component (no-op in this implementation).
   * @param deltaTime Time elapsed since the last update.
   * @param deviceContext Device context for graphics operations.
   */
  void 
  update(float deltaTime) override {}

  /**
   * @brief Renders the mesh component (no-op in this implementation).
   * @param deviceContext Device context for graphics operations.
   */
  void 
  render(DeviceContext& deviceContext) override {}

  void
    destroy() override {}

public:
  /**
   * @brief Name of the mesh.
   */
  std::string m_name;

  /**
   * @brief Vertex buffer containing the mesh's vertices.
   */
  std::vector<SimpleVertex> m_vertex;

  /**
   * @brief Index buffer containing the mesh's indices.
   */
  std::vector<unsigned int> m_index;

  /**
   * @brief Number of vertices in the mesh.
   */
  int m_numVertex;

  /**
   * @brief Number of indices in the mesh.
   */
  int m_numIndex;
};
