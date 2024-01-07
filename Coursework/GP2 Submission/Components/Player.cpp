#include "Player.h"
#include "../Other/GlobalVariables.h"
#include "../Scene/SceneManager.h"

void Player::init()
{
	// Initialize Camera
	playerCamera.initCamera(glm::vec3(0, 0, -5), 70.0f, DISPLAY_WIDTH / DISPLAY_HEIGHT, 0.01f, 1000.0f);

	SceneManager::getInstance().changeActiveCamera(playerCamera);

	playerController.init(&playerCamera, &transform);
}

void Player::onUpdate()
{
	playerController.processInput();
	playerCamera.followRot(transform, 60.0f);
}