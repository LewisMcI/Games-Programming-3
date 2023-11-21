#pragma once
#include "MainGame.h"


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

	float pos = 0;
	for (size_t i = 0; i < 1; i++)
	{
		glm::vec3 position = glm::vec3(pos, pos, pos);
		createObject(MeshType::Cube, ShaderType::Default, TextureType::Brick, position);
		pos += 30.0f;

	}

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

	std::cout << "Initialization Time = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
}


void MainGame::createObject(const MeshType& meshType, const ShaderType& shaderType, const TextureType& textureType, glm::vec3& position) {

	auto newEntity = activeScene.CreateEntity();

	TransformComponent& transform = newEntity.GetComponent<TransformComponent>();

	transform.SetPos(glm::vec3(position.x, position.y, position.z));

	newEntity.AddComponent<MaterialComponent>(shaderType, textureType, textureLoader);

	newEntity.AddComponent<MeshComponent>(meshType, masterModelLoader);
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

void MainGame::drawGame()
{	
	display.bindFBO();

	activeScene.onUpdate(player.getCamera());
	
	skybox.draw(&player.getCamera());

	display.unbindFBO();

	display.renderFBO();

	display.swapBuffer();
}