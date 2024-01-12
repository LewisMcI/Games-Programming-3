#include "Player.h"
#include "../Other/GlobalVariables.h"
#include "../Scene/SceneManager.h"

void Player::init()
{
	playerTransform = &entity.get()->GetComponent<TransformComponent>();

	SceneManager::getInstance().changeActiveCamera(playerCamera);

	playerController.init(&playerCamera, playerTransform);
}

void Player::onUpdate()
{
	playerController.processInput();
}