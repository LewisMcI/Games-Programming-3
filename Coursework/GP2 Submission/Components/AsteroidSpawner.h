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
		std::cout << "Asteroid Spawner Created" << std::endl;
	}

	ShaderType defaultShaderType = ShaderType::Default;
	TextureType defaultTextureType = TextureType::Brick;
	MeshType defaultMeshType = MeshType::Asteroid;

	void onUpdate();

protected:
private:
	void spawnAsteroid();

	void addAstroidToArray(Entity* asteroid) {
		// If we haven't hit max limit
		if (asteroidCount < MAX_ASTEROIDS)
			asteroids[asteroidCount] = asteroid;
		// If we have hit max limit
		else {
			// Try to pick empty spot

			// Try pick asteroid out of sight
			for (size_t i = 0; i < MAX_ASTEROIDS; i++)
			{
				// If distance to asteroid outside of far plane
				float distToAsteroid = glm::distance(*asteroids[i]->GetComponent<TransformComponent>().getPos(), *player.GetComponent<TransformComponent>().getPos());
				if (distToAsteroid > FAR_PLANE) {
					asteroids[i] = asteroid;
					std::cout << "Hit Max Limit: Found out of render distance, using " << i << std::endl;
					return;
				}
			}

			// Couldn't find valid 
			if (secondaryCount > MAX_ASTEROIDS)
				secondaryCount = 0;
			asteroids[secondaryCount] = asteroid;
			std::cout << "Hit Max Limit, taken first created, using " << secondaryCount << std::endl;
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