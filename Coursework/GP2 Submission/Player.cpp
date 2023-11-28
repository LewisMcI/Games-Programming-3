#include "Player.h"

void Player::init(Display& display)
{
	// Initialize Camera
	playerCamera.initCamera(glm::vec3(0, 0, -5), 70.0f, (float)display.getWidth() / display.getHeight(), 0.01f, 1000.0f);

	playerController.init(&playerCamera, &transform);
}

void Player::Update()
{
	playerController.processInput();
	playerCamera.followRot(transform, 60.0f);
}
