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
#include "TransformComponent.h"
#include "MeshComponent.h"
void MainGame::initSystems()
{
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

	display.initDisplay();

	display.initFBO();

	skybox.init();

	player.init(display);

	//createGameObject();

	auto newEntity = activeScene.CreateEntity();

	activeScene.Reg().emplace<TransformComponent>(newEntity, glm::vec3(0.0f, 0.0f, 5.0f));
	
	activeScene.Reg().emplace<MaterialComponent>(newEntity, ShaderType::Default, TextureType::Brick);
	
	activeScene.Reg().emplace<MeshComponent>(newEntity);

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

	std::cout << "Initialization Time = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
}

void MainGame::gameLoop()
{
	// While game is still playing. Processes inputs and draws the game.
	while (gameState != GameState::EXIT) 
	{
		player.Update();
		// Update Scene
		drawGame(); 
	}
}


// Draws game
void MainGame::drawGame()
{	
	// Create Blue Background
	display.clearDisplay(0.46f, 0.57f, 0.71f, 1.0f);

	display.bindFBO();

	activeScene.onUpdate(player.getCamera());
	
	skybox.draw(&player.getCamera());

	display.unbindFBO();

	display.renderFBO();

	display.swapBuffer();
}
