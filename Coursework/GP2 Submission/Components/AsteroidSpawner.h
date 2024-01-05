#pragma once


//class AsteroidSpawner {
//private:
//	ShaderType defaultShaderType = ShaderType::Default;
//	TextureType defaultTextureType = TextureType::Brick;
//	MeshType defaultMeshType = MeshType::Asteroid;
//
//public:
//	AsteroidSpawner(MeshComponent& asteroidMesh, TransformComponent& playerTransform, MainGame& mainGame) 
//		: asteroidMesh(asteroidMesh), playerTransform(playerTransform), mainGame(mainGame) {
//
//	}
//	~AsteroidSpawner();
//
//	void Update() {
//		double currTime = Time::getInstance().getCurrentTime();
//		if (currTime > nextTime) {
//			nextTime = currTime + cooldownTime;
//			SpawnAsteroid();
//		}
//	}
//protected:
//private:
//	MeshComponent& asteroidMesh;
//	TransformComponent& playerTransform;
//	MainGame& mainGame;
//
//	float cooldownTime = 5.0f;
//	double nextTime = 0.0f;
//
//	void SpawnAsteroid() {
//		// Find random position around player
//		glm::vec3& asteroidPosition = glm::vec3(0.0f);
//
//		// Spawn Entity
//		auto& newEntity = mainGame.createEntity(asteroidPosition);
//
//		newEntity.get()->AddComponent<MaterialComponent>(defaultShaderType, defaultTextureType, mainGame.textureLoader);
//
//		newEntity.get()->AddComponent<MeshComponent>(defaultMeshType, mainGame.masterModelLoader);
//	}
//};