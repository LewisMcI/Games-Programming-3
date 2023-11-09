#pragma once
#include "ModelLoader.h"

enum class MeshType { Cube, Draven, Ship };
class ModelManager {
public:
	ModelManager() = default;

	void loadModel(MeshType& meshType) {
		if (!loadedMeshes.count(meshType)) {
			std::vector<Mesh> mesh = modelLoader.loadModel(meshPaths[meshType].c_str());
			loadedMeshes.emplace(meshType, mesh);
		}
	}
	void draw(MeshType& meshType) {

		for (const auto& pair : loadedMeshes) {

			MeshType meshType = pair.first; // The key (MeshType) in the map
			const std::vector<Mesh>& meshVector = pair.second; // The associated vector of Mesh

			// Now, loop through every value in the vector
			for (const Mesh& mesh : meshVector) {
				glBindVertexArray(mesh.VAO);

				// Draw Elements
				glDrawElements(GL_TRIANGLES, (GLsizei)mesh.vertIndices.size(), GL_UNSIGNED_INT, 0);

				// Unbind
				glBindVertexArray(0);
			}
		}
	}

private:

	ModelLoader modelLoader;

	std::map<MeshType, std::string> meshPaths = {
			{MeshType::Cube, "..\\Resources\\Models\\Cube.obj"},
			{MeshType::Draven, "..\\Resources\\Models\\draven.obj"},
			{MeshType::Ship, "..\\Resources\\Models\\Ship.obj"}
	};

	// Map of MeshType and Loaded Meshes
	std::map<MeshType, std::vector<Mesh>> loadedMeshes;

};