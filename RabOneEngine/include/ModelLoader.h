#include "Prerequisites.h"
#include "MeshComponent.h"
#include "fbxsdk.h"
#pragma once

/**
 * @class ModelLoader
 * @brief Provides functionality to load, manage, and render 3D models from files.
 *
 * The ModelLoader class is responsible for initializing resources, updating state, rendering loaded models,
 * and cleaning up resources. It also provides a method to load model data from an OBJ file or similar format.
 */
class ModelLoader {
public:
  /**
   * @brief Constructs a new ModelLoader instance.
   */
  ModelLoader() = default;

  /**
   * @brief Destroys the ModelLoader instance and releases any held resources.
   */
  ~ModelLoader() = default;

  /**
   * @brief Initializes the model loader and allocates necessary resources.
   */
  void init();

  /**
   * @brief Updates the model loader state. Intended to be called once per frame.
   */
  void update();

  /**
   * @brief Renders the loaded model(s) to the current render target.
   */
  void render();

  /**
   * @brief Releases all resources and cleans up the model loader.
   */
  void destroy();

  /**
   * @brief Loads model data from the specified file.
   * @param objFileName The path to the OBJ file to load.
   * @return LoadData structure containing the loaded mesh data.
   */
  LoadData LoadOBJModel(std::string objFileName);

  /* FBX MODEL LOADER*/
  bool
  InitializeFBXManager();

  bool
  LoadFBXModel(const std::string& fileName);

  void
  ProcessFBXNode(FbxNode* node);

  void
  ProcessFBXMesh(FbxNode* node);

  void
  ProcessFBXMaterials(FbxSurfaceMaterial* material);

  std::vector<std::string>
    GetTextureFileNames() const { return textureFileNames; }

private:
  FbxManager* lSdkManager;
  FbxScene* lScene;
  std::vector<std::string> textureFileNames;
public:
  std::string modelName;
  std::vector<MeshComponent> meshes;
};
