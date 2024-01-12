#pragma once
#include "Base Scripts/ModelLoader.h"

enum class MeshType { Cube, Sphere, Ship, Asteroid1, Asteroid2, Asteroid3, R33, Laser };
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
			{MeshType::Ship, "..\\Resources\\Models\\Player Ship.fbx"},
			{MeshType::Asteroid1, "..\\Resources\\Models\\asteroid1.fbx"},
			{MeshType::Asteroid2, "..\\Resources\\Models\\asteroid2.fbx"},
			{MeshType::Asteroid3, "..\\Resources\\Models\\asteroid3.fbx"},
			{MeshType::R33, "..\\Resources\\Models\\R33.obj"},
			{MeshType::Laser, "..\\Resources\\Models\\laser.fbx"}
	};

	// Map of MeshType and Loaded Meshes
	std::map<MeshType, Model> loadedModels;
};