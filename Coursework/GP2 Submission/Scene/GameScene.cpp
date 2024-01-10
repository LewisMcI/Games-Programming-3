#pragma once
#include "GameScene.h"
#include "../Components/Player.h"
#include "../Components/AsteroidSpawner.h"

void GameScene::Load() {
	createPlayer(ShaderType::Default, TextureType::Default, MeshType::Ship);
	if (USE_INFO_DEBUGGING)
		std::cout << "Player Created" << std::endl;
	//createAsteroidSpawner();
	if (USE_INFO_DEBUGGING)
		std::cout << "Asteroid Spawner Created" << std::endl;
	
	/* Create new Entity*/
	auto& activeScene = SceneManager::getInstance().getActiveScene();

	Entity& asteroid = activeScene.get()->CreateEntity();

	asteroid.GetComponent<TransformComponent>().setPos(glm::vec3(0.0f, 0.0f, 100.0f));
	asteroid.GetComponent<TransformComponent>().setScale(glm::vec3(20.0f));

	asteroid.AddComponent<MaterialComponent>(ShaderType::Default, TextureType::Default);

	asteroid.AddComponent<MeshComponent>(MeshType::Cube);
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
}

void GameScene::createAsteroidSpawner()
{
	/* Create new Entity*/
	auto& activeScene = SceneManager::getInstance().getActiveScene();

	Entity& asteroidSpawner = activeScene.get()->CreateEntity();

	asteroidSpawner.AddComponent<AsteroidSpawner>(*player.get());
}
