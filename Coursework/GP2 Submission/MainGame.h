#pragma once

#include <SDL\SDL.h>
#include <GL/glew.h>
#include "Display.h" 
#include "Time.h"
#include "SkyBox.h"
#include "GameObject.h"
#include "Player.h"
#include "Scene/Scene.h"

enum class GameState{PLAY, EXIT};

class MainGame
{
public:

	MainGame();
	~MainGame();

	void run();

protected:
private:

	void initSystems();
	void gameLoop();
	void drawGame();

	void createGameObject();
	void drawGameObjects();

	GameState gameState;

	Display display;

	Shader shaderSkybox;
	Skybox skybox;

	Player player;

	Time time;

	Scene activeScene;
};

