#include "AsteroidSpawner.h"
#include "AsteroidMovement.h"
#include "../Other/GlobalVariables.h"
#include "Collider.h"

bool flag = false;
void AsteroidSpawner::onUpdate() {
	if (!flag) {
		for (size_t i = 0; i < MAX_ASTEROIDS * 2; i++)
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
	if (!canSpawnAsteroid())
		return;
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

	// Give asteroid random size
	float randomSize = getRandomFloat(0.25f, 1.75f);

	asteroid->GetComponent<TransformComponent>().setScale(glm::vec3(randomSize));

	asteroid->AddComponent<MeshComponent>(defaultMeshTypes[getRandomInt(0, 2)]);

	asteroid->AddComponent<Collider>(glm::vec3((5.0f)*randomSize));

	asteroid->GetComponent<TagComponent>().Tag = "Asteroid";

	asteroid->AddComponent<AsteroidMovement>();
}