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
		nextTime = currTime + (cooldownTime / TIME_STEP);
		spawnAsteroid();
		if (USE_INFO_DEBUGGING)
			std::cout << "Asteroid has been spawned" << std::endl;
	}
}

void AsteroidSpawner::spawnAsteroid() {
	// Find random position around player
	float min = -100.0f; float max = 100.0f;
	glm::vec3& asteroidPosition = *player.GetComponent<TransformComponent>().getPos() + 
		glm::vec3(getRandomFloat(min, max), getRandomFloat(min, max), getRandomFloat(min, max));

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