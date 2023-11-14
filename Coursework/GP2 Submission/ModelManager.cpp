#pragma once
#include "ModelManager.h"

void ModelManager::loadModel(MeshType& meshType) {
	if (!loadedMeshes.count(meshType)) {
		std::vector<Mesh> mesh = modelLoader.loadModel(meshPaths[meshType].c_str());
		loadedMeshes.emplace(meshType, mesh);
	}
}

void ModelManager::draw(MeshType& meshTypeToDraw) {
	for (const auto& pair : loadedMeshes) {
		// Get currentMeshType
		MeshType currMeshType = pair.first;
		// If we are not looking at the right model, move to next model
		if (currMeshType != meshTypeToDraw)
			continue;
		// Get list of meshes
		const std::vector<Mesh>& meshVector = pair.second;
		// Loop through all meshes in vector and draw
		for (const Mesh& mesh : meshVector) {
			glBindVertexArray(mesh.VAO);

			// Draw Elements
			glDrawElements(GL_TRIANGLES, (GLsizei)mesh.vertIndices.size(), GL_UNSIGNED_INT, 0);

			// Unbind
			glBindVertexArray(0);
		}
	}
}