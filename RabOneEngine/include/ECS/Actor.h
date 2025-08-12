#pragma once
#include "Prerequisites.h"
#include "Entity.h"
#include "Buffer.h"
#include "Texture.h"
#include "Transform.h"
#include "SamplerState.h"
#include "Rasterizer.h"
#include "BlendState.h"
#include "ShaderProgram.h"
#include "DepthStencilState.h"

class device;
class MeshComponent;

/**
 * @class Actor
 * @brief Represents an entity in the ECS system that can be rendered and updated.
 *
 * The Actor class extends Entity and encapsulates all the resources and logic required
 * to represent a renderable object in the scene. It manages mesh components, textures,
 * rendering states, and supports shadow casting.
 */
class Actor : public Entity {
public:
  /**
   * @brief Default constructor.
   */
  Actor() = default;

  /**
   * @brief Constructs an Actor initialized with a device.
   * @param device The device used to initialize the actor's resources.
   */
  Actor(Device& device);

  /**
   * @brief Virtual destructor.
   */
  virtual ~Actor() = default;

  /**
   * @brief Initializes the actor. (No-op override)
   */
  void init() override {}

  /**
   * @brief Updates the actor's state.
   * @param deltaTime Time elapsed since the last update.
   * @param deviceContext Device context for graphics operations.
   */
  void update(float deltaTime, DeviceContext& deviceContext) override;

  /**
   * @brief Renders the actor.
   * @param deviceContext Device context for graphics operations.
   */
  void render(DeviceContext& deviceContext) override;

  /**
   * @brief Destroys the actor and releases associated resources.
   */
  void destroy();

  /**
   * @brief Sets the mesh components for the actor.
   * @param device The device used to initialize the meshes.
   * @param meshes Vector of mesh components to assign.
   */
  void SetMesh(Device& device, std::vector<MeshComponent> meshes);

  /**
   * @brief Gets the name of the actor.
   * @return The actor's name.
   */
  std::string getName() {
    return m_name;
  }

  /**
   * @brief Sets the name of the actor.
   * @param name The new name for the actor.
   */
  void setName(const std::string& name) {
    m_name = name;
  }

  /**
   * @brief Sets the textures for the actor.
   * @param textures Vector of textures to assign.
   */
  void setTextures(std::vector<Texture> textures) {
    m_textures = textures;
  }

  /**
   * @brief Sets whether the actor can cast shadows.
   * @param v True if the actor should cast shadows, false otherwise.
   */
  void setCastShadow(bool v) {
    castShadow = v;
  }

  /**
   * @brief Checks if the actor can cast shadows.
   * @return True if the actor casts shadows, false otherwise.
   */
  bool canCastShadow() const {
    return castShadow;
  }

  /**
   * @brief Renders the actor's shadow.
   * @param deviceContext Device context for graphics operations.
   */
  void renderShadow(DeviceContext& deviceContext);

private:
  std::vector<MeshComponent> m_meshes;  ///< Mesh components associated with the actor.
  std::vector<Texture> m_textures;      ///< Textures applied to the actor.
  std::vector<Buffer> m_vertexBuffers;  ///< Vertex buffers for the actor's meshes.
  std::vector<Buffer> m_indexBuffers;   ///< Index buffers for the actor's meshes.
  BlendState m_blendstate;              ///< Blend state for rendering.
  Rasterizer m_rasterizer;              ///< Rasterizer state for rendering.
  SamplerState m_sampler;               ///< Sampler state for textures.
  CBChangesEveryFrame m_model;          ///< Per-frame constant buffer data (e.g., world matrix).
  Buffer m_modelBuffer;                 ///< Constant buffer for per-frame data.

  // Shadows
  ShaderProgram m_shaderShadow;         ///< Shader program used for shadow rendering.
  Buffer m_shaderBuffer;                ///< Buffer for shadow shader data.
  BlendState m_shadowBlendState;        ///< Blend state for shadow rendering.
  DepthStencilState m_shadowDepthStencilState; ///< Depth-stencil state for shadow rendering.
  CBChangesEveryFrame m_cbShadow;       ///< Constant buffer for shadow rendering.

  XMFLOAT4 m_LightPos;                  ///< Light position for shadow calculations.
  std::string m_name = "Actor";         ///< Name of the actor.
  bool castShadow = true;               ///< Indicates if the actor casts shadows.
};
