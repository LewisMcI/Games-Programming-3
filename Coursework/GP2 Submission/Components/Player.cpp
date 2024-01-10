#include "Player.h"
#include "../Other/GlobalVariables.h"
#include "../Scene/SceneManager.h"

void Player::init()
{
	// Initialize Camera
	playerCamera.initCamera(glm::vec3(0, 0, 0), 70.0f, DISPLAY_WIDTH / DISPLAY_HEIGHT, 0.01f, 1000.0f);

	playerTransform = &entity.get()->GetComponent<TransformComponent>();

	SceneManager::getInstance().changeActiveCamera(playerCamera);

	playerController.init(&playerCamera, playerTransform);
}

void Player::onUpdate()
{
	playerController.processInput();
	playerCamera.followTransform(*playerTransform);
}