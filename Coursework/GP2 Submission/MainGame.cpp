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
	display.initDisplay();

	activeScene = std::make_unique<Scene>();

	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

	float pos = 0;
	glm::vec3 position = glm::vec3(pos, pos, pos);
	createObject(MeshType::Box, ShaderType::Default, TextureType::Box, position);

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

	std::cout << "Initialization Time = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
}


void MainGame::createObject(const MeshType& meshType, const ShaderType& shaderType, const TextureType& textureType, glm::vec3& position) {

	player = std::make_unique<Entity>(activeScene.get()->CreateEntity());

	TransformComponent& transform = player.get()->GetComponent<TransformComponent>();

	transform.SetPos(glm::vec3(position.x, position.y, position.z));
	transform.SetRot(glm::vec3(-1.5708f, 0.0f, 3.14159f));
	transform.SetScale(glm::vec3(8.0f, 8.0f, 8.0f));

	player.get()->AddComponent<MaterialComponent>(shaderType, textureType, textureLoader);

	player.get()->AddComponent<MeshComponent>(meshType, masterModelLoader);

	Player& playerComponent = player.get()->AddComponent<Player>();
	playerComponent.init(display);
}


void MainGame::gameLoop()
{
	// While game is still playing. Processes inputs and draws the game.
	while (gameState != GameState::EXIT)
	{
		Time::getInstance().Update();
		player.get()->GetComponent<Player>().Update();
		// Update Scene
		drawGame();
	}
}

void MainGame::drawGame()
{	
	display.bindFBO();

	activeScene.get()->onUpdate(player.get()->GetComponent<Player>().getCamera());

	display.unbindFBO();

	display.renderFBO();

	display.swapBuffer();
}