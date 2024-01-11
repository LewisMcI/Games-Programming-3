#pragma once
#include "GameScene.h"
#include "../Components/Player.h"
#include "../Components/AsteroidSpawner.h"
#include "../Components/Collider.h"

void GameScene::Load() {
	createPlayer(ShaderType::Default, TextureType::Default, MeshType::Ship);
	if (USE_INFO_DEBUGGING)
		std::cout << "Player Created" << std::endl;
	createAsteroidSpawner();
	if (USE_INFO_DEBUGGING)
		std::cout << "Asteroid Spawner Created" << std::endl;

}

void GameScene::createPlayer(ShaderType shaderType, TextureType textureType, MeshType meshType)
{
	/* Create new Entity*/
	auto& activeScene = SceneManager::getInstance().getActiveScene();

	player = std::make_unique<Entity>(activeScene.get()->CreateEntity());

	player.get()->GetComponent<TransformComponent>();

	/* Set Transform*/
	TransformComponent& transform = player.get()->GetComponent<TransformComponent>();

	player.get()->AddComponent<MaterialComponent>(shaderType, textureType);

	player.get()->AddComponent<MeshComponent>(meshType);

	Player& playerComponent = player.get()->AddComponent<Player>();
	playerComponent.init();

	player.get()->AddComponent<Collider>(glm::vec3(3.0f));
}

void GameScene::createAsteroidSpawner()
{
	/* Create new Entity*/
	auto& activeScene = SceneManager::getInstance().getActiveScene();

	Entity& asteroidSpawner = activeScene.get()->CreateEntity();

	asteroidSpawner.AddComponent<AsteroidSpawner>(*player.get());
}
