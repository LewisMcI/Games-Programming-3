#pragma once
#include "PlayerController.h"
#include "../Base Scripts/Display.h"

enum CameraState { FirstPerson, ThirdPerson, FreeCam };

class Player : public Component {
public:
	Player() = default;

	void init();

	void onUpdate();

	Camera& const getCamera() {
		return playerCamera;
	}

	CameraState cameraState = CameraState::FirstPerson;

protected:
private:
	Camera playerCamera;
	PlayerController playerController;
	TransformComponent* playerTransform;
};