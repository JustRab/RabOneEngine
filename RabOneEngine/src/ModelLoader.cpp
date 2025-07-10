#include "ModelLoader.h"
#include "OBJ_Loader.h"

void ModelLoader::init()
{
}

void ModelLoader::update()
{
}

void ModelLoader::render()
{
}

void ModelLoader::destroy()
{
}

LoadData 
ModelLoader::Load(std::string objFileName) {
  objl::Loader m_loader; ///< Loader for OBJ files.
  // Temporal Load Data
  LoadData LD;

  m_loader.LoadFile(objFileName);

  LD.name = objFileName;
  WARNING("ModelLoader", "Load", L"[Load of file " + 
           std::wstring(objFileName.begin(), objFileName.end()) + L" - " +
           std::wstring(m_loader.LoadedMeshes[0].MeshName.begin(),
           m_loader.LoadedMeshes[0].MeshName.end()) + L"]");

  // Load and set data to custom structure (SimpleVertex)
  LD.vertex.resize(m_loader.LoadedVertices.size());

  for (int i = 0; i < LD.vertex.size(); i++)
  {
    // Load Positions
    LD.vertex[i].Pos.x = m_loader.LoadedVertices[i].Position.X;
    LD.vertex[i].Pos.y = m_loader.LoadedVertices[i].Position.Y;
    LD.vertex[i].Pos.z = m_loader.LoadedVertices[i].Position.Z;

    // Load Textures
    LD.vertex[i].Tex.x = m_loader.LoadedVertices[i].TextureCoordinate.X;
    LD.vertex[i].Tex.y = m_loader.LoadedVertices[i].TextureCoordinate.Y;
  }

  //Load and set data to custom structure (LoadData)
  LD.index.resize(m_loader.LoadedIndices.size());
  for (int i = 0; i < LD.index.size(); i++)
  {
    LD.index[i] = m_loader.LoadedIndices[i];
  }

  return LD;
}
