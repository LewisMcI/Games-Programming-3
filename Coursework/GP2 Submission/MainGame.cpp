#pragma once
#include "MainGame.h"

// Constructor
MainGame::MainGame()
{
	gameState = GameState::PLAY;
	// Sets up the game state.
	Display* display;
}

// Destructor
MainGame::~MainGame()
{
	gameState = GameState::EXIT;
}

void MainGame::run()
{
	initSystems();
	gameLoop();
}

#include <chrono>
void MainGame::initSystems()
{
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

	display.initDisplay();

	display.initFBO();

	skybox.init();

	player.init(display);

	createGameObject();

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

	std::cout << "Initialization Time = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
}

void MainGame::gameLoop()
{
	// While game is still playing. Processes inputs and draws the game.
	while (gameState != GameState::EXIT) 
	{
		player.Update();
		drawGame(); 
	}
}

void MainGame::createGameObject()
{
	GameObject* newObj = new GameObject();
	newObj->init(MeshType::Cube, ShaderType::Default, TextureType::Brick);
	gameObjects.push_back(newObj);
}

void MainGame::drawGameObjects() {
	int size = gameObjects.size();
	for (size_t i = 0; i < size; i++)
	{
		gameObjects.at(i)->Draw(player.getCamera());
	}
}

// Draws game
void MainGame::drawGame()
{	
	// Create Blue Background
	display.clearDisplay(0.46f, 0.57f, 0.71f, 1.0f);

	display.bindFBO();

	drawGameObjects();
	
	skybox.draw(&player.getCamera());

	display.unbindFBO();

	display.renderFBO();

	display.swapBuffer();
}
