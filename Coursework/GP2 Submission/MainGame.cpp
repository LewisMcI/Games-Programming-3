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

void MainGame::initSystems()
{
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

	display.initDisplay();

	skybox.init();

	player.init(display);

	for (size_t i = 0; i < 1; i++)
	{
		for (size_t j = 0; j < 1; j++)
		{
			for (size_t k = 0; k < 1; k++) {

				auto newEntity = activeScene.CreateEntity();

				TransformComponent& transform = newEntity.GetComponent<TransformComponent>();
				transform.SetPos(glm::vec3(i, j, k));

				newEntity.AddComponent<MaterialComponent>(ShaderType::EnviromentMapping, TextureType::Default, textureLoader);

				newEntity.AddComponent<MeshComponent>(MeshType::Cube, meshloader);
			}
		}
	}
	

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

	std::cout << "Initialization Time = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
}

void MainGame::gameLoop()
{
	// While game is still playing. Processes inputs and draws the game.
	while (gameState != GameState::EXIT) 
	{
		Time::getInstance().Update();
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