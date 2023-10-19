#pragma once
#include "PlayerController.h"
#include "Display.h"
class Player {
public:
	Player();

	void init(Display& display);

	void Update();

	Camera& const getCamera() {
		return playerCamera;
	}
protected:
private:
	Camera playerCamera;
	PlayerController playerController;
};