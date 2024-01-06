#pragma once
#include "ModelLoader.h"

enum class MeshType { Cube, Sphere, Ship, Asteroid, R33 };
class ModelManager {
public:
	ModelManager() = default;

	static ModelManager& getInstance() {
		static ModelManager instance;
		return instance;
	}

	void loadModel(MeshType& meshType);
	void draw(MeshType& meshType);

	std::string SerializeMeshToJson(const Model& model);

	bool SaveJsonToFile(const std::string& json, const std::string& filename);

	std::string LoadJsonFromFile(const std::string& filename);

	Model RecreateModelFromJson(const std::string& json);

private:
	ModelLoader modelLoader;

	// Map of MeshType and Mesh Paths
	std::map<MeshType, std::string> meshPaths = {
			{MeshType::Cube, "..\\Resources\\Models\\Cube.obj"},
			{MeshType::Sphere, "..\\Resources\\Models\\Sphere.obj"},
			{MeshType::Ship, "..\\Resources\\Models\\Ship.obj"},
			{MeshType::Asteroid, "..\\Resources\\Models\\Asteroid.obj"},
			{MeshType::R33, "..\\Resources\\Models\\R33.obj"}
	};

	// Map of MeshType and Loaded Meshes
	std::map<MeshType, Model> loadedModels;
};