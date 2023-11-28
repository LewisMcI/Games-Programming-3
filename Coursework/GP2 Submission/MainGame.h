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

enum class GameState{PLAY, EXIT};

class MainGame
{
public:

	MainGame() {};
	~MainGame();

	void run();

protected:
private:

	void initSystems();
	void createObject(const MeshType& meshType, const ShaderType& shaderType, const TextureType& textureType, glm::vec3& position);
	void createPlayer(const MeshType& meshType, const ShaderType& shaderType, const TextureType& textureType, glm::vec3& position);
	void createNumOfCubes(int amount, glm::vec3& centerPoint);
	void gameLoop();
	void drawGame();

	GameState gameState;

	Display display;

	Shader shaderSkybox;

	std::unique_ptr<Entity> player;

	std::unique_ptr<Scene> activeScene;

	TextureLoader textureLoader;

	ModelManager masterModelLoader;

};

