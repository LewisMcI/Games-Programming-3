#pragma once
#include "Component.h"
#include "MaterialComponent.h"
#include "MeshComponent.h"
#include "../Scene/Entity.h"
#include "../Scene/SceneManager.h"
#include "../Base Scripts/Time.h"
const int MAX_ASTEROIDS = 100;
class AsteroidSpawner : public Component {
public:
	AsteroidSpawner(Entity& player) : player(player) {
		if (USE_INFO_DEBUGGING)
			std::cout << "Asteroid Spawner Created" << std::endl;
	}

	ShaderType defaultShaderType = ShaderType::Default;
	TextureType defaultTextureType = TextureType::Brick;
	MeshType defaultMeshType = MeshType::Asteroid;

	void onUpdate();

protected:
private:
	float getRandomFloat(float high, float low) {
		return low + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (high - low)));
	}

	void spawnAsteroid();

	void addAstroidToArray(Entity* asteroid) {
		// If we haven't hit max limit
		if (asteroidCount < MAX_ASTEROIDS)
			asteroids[asteroidCount] = asteroid;

		// If we have hit max limit
		else {
			// Try pick asteroid out of sight
			for (size_t i = 0; i < MAX_ASTEROIDS; i++)
			{
				// If distance to asteroid outside of far plane
				float distToAsteroid = glm::distance(*asteroids[i]->GetComponent<TransformComponent>().getPos(), *player.GetComponent<TransformComponent>().getPos());
				if (distToAsteroid > FAR_PLANE) {
					asteroids[i] = asteroid;
					if (USE_INFO_DEBUGGING)
						std::cout << "Asteroid Spawner: Hit Max Limit: Found out of render distance, using " << i << std::endl;
					return;
				}
			}

			// Couldn't find valid - Use first made
			if (secondaryCount > MAX_ASTEROIDS - 1)
				secondaryCount = 0;
			asteroids[secondaryCount] = asteroid;
			if (USE_INFO_DEBUGGING)
				std::cout << "Asteroid Spawner: Hit Max Limit, taken first created, using " << secondaryCount << std::endl;
			secondaryCount++;

		}
	}

	float cooldownTime = 1.0f;
	double nextTime = 0.0f;

	int asteroidCount = 0;

	int secondaryCount = 0;

	Entity* asteroids[MAX_ASTEROIDS];

	Entity& player;
};