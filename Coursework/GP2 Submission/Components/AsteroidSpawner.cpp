#include "AsteroidSpawner.h"
#include "AsteroidMovement.h"
#include "../Other/GlobalVariables.h"
#include "Collider.h"

bool flag = false;
void AsteroidSpawner::onUpdate() {
	if (!flag) {
		for (size_t i = 0; i < 110; i++)
		{
			spawnAsteroid();
		}
		flag = true;
	}
	double currTime = Time::getInstance().getCurrentTime();
	if (currTime > nextTime) {
		nextTime = currTime + cooldownTime;
		spawnAsteroid();
		if (USE_INFO_DEBUGGING)
			std::cout << "Asteroid has been spawned" << std::endl;
	}
}

void AsteroidSpawner::spawnAsteroid() {
	// Find random position around player
	glm::vec3& asteroidPosition = *player.GetComponent<TransformComponent>().getPos() + glm::vec3(0.0f, 0.0f, 50.0f);

	// Spawn Entity
	auto& activeScene = SceneManager::getInstance().getActiveScene();

	Entity* asteroid = new Entity(activeScene.get()->CreateEntity("Asteroid", asteroidPosition));

	addAstroidToArray(asteroid);

	asteroidCount++;

	asteroid->AddComponent<MaterialComponent>(defaultShaderType, defaultTextureType);

	asteroid->AddComponent<MeshComponent>(defaultMeshType);

	asteroid->AddComponent<Collider>(glm::vec3(20.0f));

	asteroid->GetComponent<TagComponent>().Tag = "Asteroid";

	asteroid->AddComponent<AsteroidMovement>();
}