#pragma once
#include "GameScene.h"

void GameScene::Load() {
	createPlayer(ShaderType::Default, TextureType::Metal, MeshType::Ship);
	createAsteroidSpawner();
}

void GameScene::createPlayer(ShaderType shaderType, TextureType textureType, MeshType meshType)
{
	/* Create new Entity*/
	auto& activeScene = SceneManager::getInstance().getActiveScene();

	std::unique_ptr<Entity> player = std::make_unique<Entity>(activeScene.get()->CreateEntity());

	player.get()->GetComponent<TransformComponent>();

	/* Set Transform*/
	TransformComponent& transform = player.get()->GetComponent<TransformComponent>();

	transform.setPos(glm::vec3(0.0f, 0.0f, 0.0f));
	transform.setRot(glm::vec3(0.0f, 0.0f, 0.0f));
	transform.setScale(glm::vec3(.1f, .1f, .1f));

	player.get()->AddComponent<MaterialComponent>(shaderType, textureType);

	player.get()->AddComponent<MeshComponent>(meshType);

	Player& playerComponent = player.get()->AddComponent<Player>(transform);
	playerComponent.init();
}

void GameScene::createAsteroidSpawner()
{
	/* Create new Entity*/
	auto& activeScene = SceneManager::getInstance().getActiveScene();

	Entity& entAsteroidSpawner = activeScene.get()->CreateEntity();

	std::cout << "adding asteroid component" << std::endl;
	entAsteroidSpawner.AddComponent<AsteroidSpawner>();
}
