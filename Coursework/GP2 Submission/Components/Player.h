#pragma once
#include "PlayerController.h"
#include "../Base Scripts/Display.h"

class Player : public Component {
public:
	Player() = default;

	void init();

	void onUpdate();

	Camera& const getCamera() {
		return playerCamera;
	}
protected:
private:
	Camera playerCamera;
	PlayerController playerController;
	TransformComponent* playerTransform;
};