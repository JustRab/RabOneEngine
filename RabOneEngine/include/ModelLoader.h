#pragma once
#include "Prerequisites.h"
#include "MeshComponent.h"

/**
 * @class ModelLoader
 * @brief Utility class for loading 3D models from OBJ files and extracting mesh data.
 *
 * The ModelLoader class provides methods to load models from OBJ files using a custom parser,
 * extract mesh and material information, and store the results in MeshComponent objects.
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
   * Parses the OBJ file using the custom OBJ parser and extracts vertex, index, and material information.
   */
  MeshComponent LoadOBJModel(const std::string& filePath);

public:
  std::string modelName;                    ///< Name of the loaded model.
  std::vector<MeshComponent> meshes;        ///< Mesh components extracted from the model.
};
