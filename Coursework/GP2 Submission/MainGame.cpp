#pragma once
#include "MainGame.h"

void MainGame::runGame()
{
	initSystems();
	gameLoop();
}

void MainGame::initSystems() {
	std::cout << "Intialization times:" << std::endl;
	std::cout << "_______________________" << std::endl;

	displayFunctionTime("Display", [this]() { display.initDisplay(); });
	displayFunctionTime("Scene", [this]() { SceneManager::getInstance().createNewScene(); });
	displayFunctionTime("Game Scene", [this]() { gameScene.Load(); });

	std::cout << "_______________________" << std::endl;
}

void MainGame::gameLoop()
{
	/* While game is running */
	while (gameState != GameState::EXIT)
	{
		/* Time Update */
		Time::getInstance().onUpdate();
		/* Call onUpdate on all components within scene*/
		SceneManager::getInstance().getActiveScene().get()->onUpdate();
		/* Rendering */
		drawGame();
	}
}

void MainGame::drawGame()
{	
	display.bindFBO();

	SceneManager::getInstance().getActiveScene().get()->draw();

	display.unbindFBO();

	display.renderFBO();

	display.swapBuffer();
}