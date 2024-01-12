#pragma once
#include "Component.h"
#include "MaterialComponent.h"
#include "MeshComponent.h"
#include "../Scene/Entity.h"
#include "../Scene/SceneManager.h"
#include "../Base Scripts/Time.h"
#include "Collider.h"

class AsteroidSpawner : public Component {
public:
	AsteroidSpawner(Entity& player) : player(player) {
		if (USE_INFO_DEBUGGING)
			std::cout << "Asteroid Spawner Created" << std::endl;
	}

	~AsteroidSpawner() {
		for (int i = 0; i < MAX_ASTEROIDS; ++i) {
			if (asteroids[i] != nullptr) {
				delete asteroids[i];
				asteroids[i] = nullptr;
			}
		}
	}

	ShaderType defaultShaderType = ShaderType::Default;
	TextureType defaultTextureType = TextureType::Asteroid;
	MeshType defaultMeshTypes[3] = {
		MeshType::Asteroid1,
		MeshType::Asteroid2,
		MeshType::Asteroid3
	};

	void onUpdate();

protected:
private:
	float getRandomFloat(float high, float low) {
		return low + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (high - low)));
	}

	int getRandomInt(int low, int high) {
		return rand() % (high - low + 1) + low;
	}
	void spawnAsteroid();

	void addAstroidToArray(Entity* asteroid) {
		// If we haven't hit max limit
		if (asteroidCount < MAX_ASTEROIDS) {
			asteroids[asteroidCount] = asteroid;
		}

		// If we have hit max limit
		else {
			// Try pick asteroid out of sight
			for (size_t i = 0; i < MAX_ASTEROIDS; i++)
			{
				if (!asteroids[i]->HasComponent<Collider>())
				{
					asteroids[i] = asteroid;
					if (USE_INFO_DEBUGGING)
						std::cout << "Asteroid Spawner: Hit Max Limit: Found out of render distance, using " << i << std::endl;
					return;
				}
				// If distance to asteroid outside of far plane
				float distToAsteroid = glm::distance(*asteroids[i]->GetComponent<TransformComponent>().getPos(), *player.GetComponent<TransformComponent>().getPos());
				if (distToAsteroid > FAR_PLANE) {
					asteroids[i]->RemoveComponent<Collider>();
					asteroids[i]->RemoveComponent<MeshComponent>();
					asteroids[i] = asteroid;
					if (USE_INFO_DEBUGGING)
						std::cout << "Asteroid Spawner: Hit Max Limit: Found out of render distance, using " << i << std::endl;
				}
			}

		}
	}

	bool canSpawnAsteroid() {
		if (asteroidCount < MAX_ASTEROIDS) {
			return true;
		}

		// Try pick asteroid out of sight
		for (size_t i = 0; i < MAX_ASTEROIDS; i++)
		{
			// If object has been destroyed
			if (!asteroids[i]->HasComponent<Collider>())
				return true;
			// If distance to asteroid outside of far plane
			float distToAsteroid = glm::distance(*asteroids[i]->GetComponent<TransformComponent>().getPos(), *player.GetComponent<TransformComponent>().getPos());
			if (distToAsteroid > FAR_PLANE) {
				return true;
			}
		}
		return false;
	}

	float cooldownTime = 0.01f;
	double nextTime = 0.0f;

	int asteroidCount = 0;

	int secondaryCount = 0;

	Entity* asteroids[MAX_ASTEROIDS];

	Entity& player;
};