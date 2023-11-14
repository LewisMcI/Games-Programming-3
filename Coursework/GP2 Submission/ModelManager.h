#pragma once
#include "ModelLoader.h"

enum class MeshType { Cube, Draven, Ship };
class ModelManager {
public:
	ModelManager() = default;

	void loadModel(MeshType& meshType);
	void draw(MeshType& meshType);

private:
	ModelLoader modelLoader;

	// Map of MeshType and Mesh Paths
	std::map<MeshType, std::string> meshPaths = {
			{MeshType::Cube, "..\\Resources\\Models\\Cube.obj"},
			{MeshType::Draven, "..\\Resources\\Models\\draven.obj"},
			{MeshType::Ship, "..\\Resources\\Models\\Ship.obj"}
	};

	// Map of MeshType and Loaded Meshes
	std::map<MeshType, std::vector<Mesh>> loadedMeshes;
	bool lookForModelBinary(std::string meshPath);
	void writeModelBinary(MeshType& meshType);
	void readModelBinary(std::string meshPath);
};