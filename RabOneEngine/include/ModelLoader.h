#pragma once
#include "Prerequisites.h"
#include "MeshComponent.h"
#include "fbxsdk.h"

/**
 * @class ModelLoader
 * @brief Utility class for loading 3D models (OBJ and FBX) and extracting mesh and texture data.
 *
 * The ModelLoader class provides methods to load models from OBJ and FBX files, process their nodes,
 * extract mesh and material information, and store the results in MeshComponent objects. It also
 * manages FBX SDK resources and collects texture file names referenced by the model.
 */
class ModelLoader {
public:
  /**
   * @brief Default constructor.
   */
  ModelLoader() = default;

  /**
   * @brief Destructor.
   */
  ~ModelLoader() = default;

  /**
   * @brief Loads a model from an OBJ file.
   * @param filePath Path to the OBJ file.
   * @return MeshComponent containing the loaded mesh data.
   *
   * Parses the OBJ file and extracts vertex, index, and material information.
   */
  MeshComponent LoadOBJModel(const std::string& filePath);

  /**
   * @brief Initializes the FBX SDK manager and scene.
   * @return True if initialization was successful, false otherwise.
   *
   * This method must be called before loading FBX models.
   */
  bool InitializeFBXManager();

  /**
   * @brief Loads a model from an FBX file.
   * @param filePath Path to the FBX file.
   * @return True if the model was loaded successfully, false otherwise.
   *
   * Loads the FBX file, processes its nodes, and extracts mesh and material data.
   */
  bool LoadFBXModel(const std::string& filePath);

  /**
   * @brief Recursively processes an FBX node and its children.
   * @param node Pointer to the FBX node to process.
   *
   * Extracts mesh and material data from the node and its descendants.
   */
  void ProcessFBXNode(FbxNode* node);

  /**
   * @brief Processes an FBX node containing mesh data.
   * @param node Pointer to the FBX node with mesh data.
   *
   * Extracts vertex and index data from the mesh and stores it in MeshComponent objects.
   */
  void ProcessFBXMesh(FbxNode* node);

  /**
   * @brief Processes an FBX material to extract texture file names.
   * @param material Pointer to the FBX surface material.
   *
   * Collects texture file names referenced by the material for later use.
   */
  void ProcessFBXMaterials(FbxSurfaceMaterial* material);

  /**
   * @brief Gets the list of texture file names referenced by the loaded model.
   * @return Vector of texture file names.
   */
  std::vector<std::string> GetTextureFileNames() const { return textureFileNames; }

private:
  FbxManager* lSdkManager;                  ///< Pointer to the FBX SDK manager.
  FbxScene* lScene;                         ///< Pointer to the FBX scene.
  std::vector<std::string> textureFileNames;///< List of texture file names found in the model.

public:
  std::string modelName;                    ///< Name of the loaded model.
  std::vector<MeshComponent> meshes;        ///< Mesh components extracted from the model.
};
