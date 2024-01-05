#pragma once
#define SDL_MAIN_HANDLED 
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include "Display.h" 
#include "Time.h"
#include "SkyBox.h"
#include "GameObject.h"
#include "Player.h"
#include "Scene/Scene.h"]
#include <chrono>
#include "Components/MeshComponent.h"
#include "Scene/Entity.h";
#include "Components/MaterialComponent.h"
#include "ModelManager.h"
#include "Components/AsteroidSpawner.h"

enum class GameState{PLAY, EXIT};

class MainGame
{
public:

	MainGame() {};
	~MainGame();

	void run();

	auto& createEntity(glm::vec3& position = glm::vec3(0.0f), glm::vec3& rotation = glm::vec3(0.0f), glm::vec3& scale = glm::vec3(1.0f)) {

		auto newEntity = std::make_unique<Entity>(activeScene.get()->CreateEntity());

		TransformComponent& transform = newEntity.get()->GetComponent<TransformComponent>();

		transform.setPos(glm::vec3(position.x, position.y, position.z));
		transform.setRot(glm::vec3(rotation.x, rotation.y, rotation.z));
		transform.setScale(glm::vec3(scale.x, scale.y, scale.z));

		return newEntity;
	}

	TextureLoader textureLoader;

	ModelManager masterModelLoader;

protected:
private:

	void initSystems();
	void createObject(const MeshType& meshType, const ShaderType& shaderType, const TextureType& textureType, glm::vec3& position);
	void createPlayer(const MeshType& meshType, const ShaderType& shaderType, const TextureType& textureType, glm::vec3& position);
	void gameLoop();
	void drawGame();

	GameState gameState;

	Display display;

	Shader shaderSkybox;

	std::unique_ptr<Entity> player;

	std::unique_ptr<Scene> activeScene;

};

