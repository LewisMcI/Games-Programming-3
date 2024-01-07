#include "AsteroidSpawner.h"

void AsteroidSpawner::onUpdate() {
	double currTime = Time::getInstance().getCurrentTime();
	if (currTime > nextTime) {
		nextTime = currTime + cooldownTime;
		SpawnAsteroid();
	}
}

void AsteroidSpawner::SpawnAsteroid() {
	std::cout << "Spawning Asteroid" << std::endl;
	// Find random position around player
	glm::vec3& asteroidPosition = glm::vec3(10.0f, 0.0f, 0.0f);

	// Spawn Entity
	auto& activeScene = SceneManager::getInstance().getActiveScene();

	Entity* newEntity = new Entity(activeScene.get()->CreateEntity());

	listOfAsteroids.push_back(newEntity);

	asteroidCount++;

	newEntity->AddComponent<MaterialComponent>(defaultShaderType, defaultTextureType);

	newEntity->AddComponent<MeshComponent>(defaultMeshType);

	newEntity->AddComponent<AsteroidMovement>();
}