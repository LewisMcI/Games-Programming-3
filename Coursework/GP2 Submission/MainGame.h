#pragma once
#define SDL_MAIN_HANDLED 
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include "Display.h" 
#include "Time.h"
#include "SkyBox.h"
#include "GameObject.h"
#include "Player.h"
#include <chrono>
#include "Components/MeshComponent.h"
#include "Scene/Entity.h";
#include "Components/MaterialComponent.h"
#include "ModelManager.h"
#include "Components/AsteroidSpawner.h"
#include "Scene/SceneManager.h"
#include "Scene/GameScene.h"

enum class GameState{PLAY, EXIT};

class MainGame
{
public:

	MainGame() {};
	~MainGame() {
		gameState = GameState::EXIT;
	}

	void runGame();

protected:
private:

	void initSystems();

	void gameLoop();

	void drawGame();

	void displayFunctionTime(const std::string& taskName, std::function<void()> initializationFunction) {
		std::chrono::steady_clock::time_point begin, end;

		begin = std::chrono::steady_clock::now();

		initializationFunction();

		end = std::chrono::steady_clock::now();

		std::cout << taskName << " = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
	}

	GameState gameState;

	Display display;

	GameScene gameScene;
};

