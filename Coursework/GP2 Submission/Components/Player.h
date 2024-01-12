#pragma once
#include "PlayerController.h"
#include "../Base Scripts/Display.h"

enum CameraState { FirstPerson, ThirdPerson, FreeCam };

class Player : public Component {
public:
	Player() : playerCamera(Camera(glm::vec3(0, 0, 0), 70.0f, DISPLAY_WIDTH / DISPLAY_HEIGHT, NEAR_PLANE, FAR_PLANE)){
	}

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