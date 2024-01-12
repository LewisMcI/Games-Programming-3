#include "Player.h"
#include "../Other/GlobalVariables.h"
#include "../Scene/SceneManager.h"

void Player::init()
{
	// Initialize Camera
	playerCamera.initCamera(glm::vec3(0, 0, 0), 70.0f, DISPLAY_WIDTH / DISPLAY_HEIGHT, NEAR_PLANE, FAR_PLANE);

	playerTransform = &entity.get()->GetComponent<TransformComponent>();

	SceneManager::getInstance().changeActiveCamera(playerCamera);

	playerController.init(&playerCamera, playerTransform);
}

void Player::onUpdate()
{
	playerController.processInput();
	if (cameraState == FirstPerson)
		playerCamera.followTransform(*playerTransform);
	else if (cameraState == ThirdPerson)
		playerCamera.lookAtTransform(*playerTransform, 5.0f);
}