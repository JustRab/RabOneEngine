#pragma once
#include "Prerequisites.h"
#include "ECS/Entity.h"
#include "Buffer.h"
#include "Texture.h"

class device;
class MeshComponent;

class Actor : public Entity {
public:
	Actor() = default;

	Actor(Device& device);

	virtual
	~Actor() = default;

  void
  update(float deltaTime, DeviceContext& deviceContext) override;

  void
  render(DeviceContext& deviceContext) override;

  void
  destroy();

  void
  SetMesh(Device& device, std::vector<MeshComponent> meshes);

  std::string
    getName() {
    return m_name; 
  }

  void
  setName(const std::string& name) {
    m_name = name;
  }

private:
  std::vector<MeshComponent> m_meshes; ///< Vector of mesh components associated with the actor.
  std::vector<Texture> m_textures; ///< Vector of textures associated with the actor.
  std::vector<Buffer> m_vertexBuffers; ///< Vector of buffers associated with the actor.
  std::vector<Buffer> m_indexBuffers; ///< Vector of index buffers associated with the actor.
  CBChangesEveryFrame m_model; ///< Constant buffer for model transformations and mesh color.
  Buffer m_modelBuffer; ///< Buffer for the model constant buffer.
  std::string m_name = "Actor"; ///< Name of the actor.
  bool castShadow = false; ///< Flag indicating if the actor casts shadows.
};
