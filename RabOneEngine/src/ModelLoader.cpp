#include "ModelLoader.h"
#include "OBJ_Loader.h"

MeshComponent
ModelLoader::LoadOBJModel(const std::string& filePath) {
	MeshComponent mesh;
	objl::Loader loader;

	if (!loader.LoadFile(filePath)) {
		return mesh;
	}

	mesh.m_name = filePath;

	const unsigned int numVertices = loader.LoadedVertices.size();
	const unsigned int numIndices = loader.LoadedIndices.size();

	// Reservar memoria exacta para evitar reallocs
	mesh.m_vertex.resize(numVertices);
	mesh.m_index = std::move(loader.LoadedIndices);  // Mover directamente

	// Usar acceso por índice para evitar cópias extra
	for (unsigned int i = 0; i < numVertices; ++i) {
		const auto& v = loader.LoadedVertices[i];

		mesh.m_vertex[i] = SimpleVertex{
			{ v.Position.X, v.Position.Y, v.Position.Z },
			{ v.TextureCoordinate.X, v.TextureCoordinate.Y }  // Remove UV flipping
		};
	}

	mesh.m_numVertex = numVertices;
	mesh.m_numIndex = numIndices;

	return mesh;
}