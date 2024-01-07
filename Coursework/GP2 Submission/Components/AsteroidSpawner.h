#pragma once
#include "Component.h"
#include "MaterialComponent.h"
#include "MeshComponent.h"
#include "../Scene/Entity.h"
#include "../Scene/SceneManager.h"
#include "../Base Scripts/Time.h"

class AsteroidSpawner : public Component {
public:
	AsteroidSpawner() {
		std::cout << "Asteroid Spawner Created" << std::endl;
	}

	ShaderType defaultShaderType = ShaderType::Default;
	TextureType defaultTextureType = TextureType::Brick;
	MeshType defaultMeshType = MeshType::Asteroid;

	void onUpdate();

protected:
private:

	float cooldownTime = 5.0f;
	double nextTime = 0.0f;

	int asteroidCount = 0;
	std::vector<Entity*> listOfAsteroids;
	void SpawnAsteroid();
};