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


bool
ModelLoader::InitializeFBXManager() {
	// Initialize the FBX SDK manager
	lSdkManager = FbxManager::Create();
	if (!lSdkManager) {
		ERROR("ModelLoader", "FbxManager::Create()", "Unable to create FBX Manager!");
		return false;
	}
	else {
		MESSAGE("ModelLoader", "ModelLoader", "Autodesk FBX SDK version " << lSdkManager->GetVersion())
	}

	// Create an IOSettings object
	FbxIOSettings* ios = FbxIOSettings::Create(lSdkManager, IOSROOT);
	lSdkManager->SetIOSettings(ios);

	// Create an FBX Scene
	lScene = FbxScene::Create(lSdkManager, "MyScene");
	if (!lScene) {
		ERROR("ModelLoader", "FbxScene::Create()", "Unable to create FBX Scene!");
		return false;
	}
	else {
		MESSAGE("ModelLoader", "ModelLoader", "FBX Scene created successfully.")
	}
	return true;
}

bool
ModelLoader::LoadFBXModel(const std::string& filePath) {
	// Clear previous mesh data
	meshes.clear();
	textureFileNames.clear();

	// 01. Initialize the SDK from FBX Manager
	if (InitializeFBXManager()) {
		// 02. Create an importer using the SDK manager
		FbxImporter* lImporter = FbxImporter::Create(lSdkManager, "");
		if (!lImporter) {
			ERROR("ModelLoader", "FbxImporter::Create()", "Unable to create FBX Importer!");
			return false;
		}
		else {
			MESSAGE("ModelLoader", "ModelLoader", "FBX Importer created successfully.");
		}

		// 03. Use the first argument as the filename for the importer
		if (!lImporter->Initialize(filePath.c_str(), -1, lSdkManager->GetIOSettings())) {
			ERROR("ModelLoader", "FbxImporter::Initialize()",
				"Unable to initialize FBX Importer! Error: " << lImporter->GetStatus().GetErrorString());
			lImporter->Destroy();
			return false;
		}
		else {
			MESSAGE("ModelLoader", "ModelLoader", "FBX Importer initialized successfully.");
		}

		// 04. Import the scene from the file into the scene
		if (!lImporter->Import(lScene)) {
			ERROR("ModelLoader", "FbxImporter::Import()",
				"Unable to import FBX Scene! Error: " << lImporter->GetStatus().GetErrorString());
			lImporter->Destroy();
			return false;
		}
		else {
			MESSAGE("ModelLoader", "ModelLoader", "FBX Scene imported successfully.");
			modelName = lImporter->GetFileName();
		}

		// 05. Destroy the importer
		lImporter->Destroy();
		MESSAGE("ModelLoader", "ModelLoader", "FBX Importer destroyed successfully.");

		// 06. Process the model from the scene
		FbxNode* lRootNode = lScene->GetRootNode();

		if (lRootNode) {
			MESSAGE("ModelLoader", "ModelLoader", "Processing model from the scene root node.");
			for (int i = 0; i < lRootNode->GetChildCount(); i++) {
				ProcessFBXNode(lRootNode->GetChild(i));
			}
			return !meshes.empty(); // Return true only if we loaded meshes
		}
		else {
			ERROR("ModelLoader", "FbxScene::GetRootNode()",
				"Unable to get root node from FBX Scene!");
			return false;
		}
	}
	return false;
}

void
ModelLoader::ProcessFBXNode(FbxNode* node) {
	// 01. Process all the node's meshes
	if (node->GetNodeAttribute()) {
		if (node->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eMesh) {
			ProcessFBXMesh(node);
		}
	}

	// 02. Recursively process each child node
	for (int i = 0; i < node->GetChildCount(); i++) {
		ProcessFBXNode(node->GetChild(i));
	}
}

void
ModelLoader::ProcessFBXMesh(FbxNode* node) {
	// 01. Get the mesh from the node. If there is no mesh, exit early.
	FbxMesh* mesh = node->GetMesh();
	if (!mesh) return;

	// Triangulate the mesh to ensure we have triangles
	FbxGeometryConverter converter(lSdkManager);
	mesh = (FbxMesh*)converter.Triangulate(mesh, true);
	if (!mesh) {
		ERROR("ModelLoader", "ProcessFBXMesh", "Failed to triangulate mesh");
		return;
	}

	std::vector<SimpleVertex> vertices;
	std::vector<unsigned int> indices;

	// 02. Get UV element
	FbxGeometryElementUV* uvElement = nullptr;
	if (mesh->GetElementUVCount() > 0) {
		uvElement = mesh->GetElementUV(0);
	}

	// 03. Process each polygon (should be triangles after triangulation)
	int vertexId = 0;
	for (int polyIndex = 0; polyIndex < mesh->GetPolygonCount(); polyIndex++) {
		int polySize = mesh->GetPolygonSize(polyIndex);

		// Should be 3 after triangulation
		if (polySize != 3) {
			ERROR("ModelLoader", "ProcessFBXMesh", "Non-triangle polygon found after triangulation");
			continue;
		}

		// Process each vertex in the triangle
		for (int vertIndex = 0; vertIndex < polySize; vertIndex++) {
			int controlPointIndex = mesh->GetPolygonVertex(polyIndex, vertIndex);

			SimpleVertex vertex;

			// Get position from control points
			FbxVector4 position = mesh->GetControlPointAt(controlPointIndex);
			vertex.Pos = XMFLOAT3(
				static_cast<float>(position[0]),
				static_cast<float>(position[1]),
				static_cast<float>(position[2])
			);

			// Get UV coordinates - Fixed UV mapping
			if (uvElement) {
				FbxVector2 uv(0, 0);

				// Use polygon vertex mapping for proper per-vertex UV coordinates
				if (uvElement->GetMappingMode() == FbxGeometryElement::eByPolygonVertex) {
					if (uvElement->GetReferenceMode() == FbxGeometryElement::eDirect) {
						uv = uvElement->GetDirectArray().GetAt(vertexId);
					}
					else if (uvElement->GetReferenceMode() == FbxGeometryElement::eIndexToDirect) {
						int uvIndex = uvElement->GetIndexArray().GetAt(vertexId);
						uv = uvElement->GetDirectArray().GetAt(uvIndex);
					}
				}
				else if (uvElement->GetMappingMode() == FbxGeometryElement::eByControlPoint) {
					if (uvElement->GetReferenceMode() == FbxGeometryElement::eDirect) {
						uv = uvElement->GetDirectArray().GetAt(controlPointIndex);
					}
					else if (uvElement->GetReferenceMode() == FbxGeometryElement::eIndexToDirect) {
						int uvIndex = uvElement->GetIndexArray().GetAt(controlPointIndex);
						uv = uvElement->GetDirectArray().GetAt(uvIndex);
					}
				}

				// Clamp UV coordinates to valid range and fix V coordinate if needed
				float u = static_cast<float>(uv[0]);
				float v = static_cast<float>(uv[1]);

				// Ensure UV coordinates are in valid range
				u = fmod(u, 1.0f);
				v = fmod(v, 1.0f);
				if (u < 0.0f) u += 1.0f;
				if (v < 0.0f) v += 1.0f;

				vertex.Tex = XMFLOAT2(u, -v);
			}
			else {
				vertex.Tex = XMFLOAT2(0.0f, 0.0f);
			}

			vertices.push_back(vertex);
			indices.push_back(vertexId);
			vertexId++;
		}
	}

	// 04. Create a MeshComponent and populate it with the processed data.
	if (!vertices.empty() && !indices.empty()) {
		MeshComponent meshData;
		meshData.m_name = node->GetName();
		meshData.m_vertex = vertices;
		meshData.m_index = indices;
		meshData.m_numVertex = vertices.size();
		meshData.m_numIndex = indices.size();

		// 05. Add the processed mesh data to the collection.
		meshes.push_back(meshData);
	}
}

void
ModelLoader::ProcessFBXMaterials(FbxSurfaceMaterial* material) {
	if (material) {
		FbxProperty prop = material->FindProperty(FbxSurfaceMaterial::sDiffuse);
		if (prop.IsValid()) {
			int textureCount = prop.GetSrcObjectCount<FbxTexture>();
			for (int i = 0; i < textureCount; ++i) {
				FbxTexture* texture = FbxCast<FbxTexture>(prop.GetSrcObject<FbxTexture>(i));
				if (texture) {
					textureFileNames.push_back(texture->GetName());
				}
			}
		}
	}
}