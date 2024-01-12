#pragma once
#define SDL_MAIN_HANDLED 
#include "../Base Scripts/Camera.h"
#include <SDL2/SDL_events.h>
#include <iostream>
#include "../Base Scripts/Time.h"
#include "TransformComponent.h"

class PlayerController
{
public:
	PlayerController();
	~PlayerController() {
		for (Entity* bullet : bulletList) {
			delete bullet;
			bullet = nullptr;
		}
	}

	void init(Camera* camera, TransformComponent* transform);

	void processInput();
	
	void processKeyboardInput(const Uint8* keys);

	void processMouseInput();

	void processFreecamInput();

	void processFreecamKeyboardInput(const Uint8* keys);

	void processFreecamMouseInput();
protected:
private:
	void shootBullet(glm::vec3 pos);

	TransformComponent* playerTransform;

	Camera* playerCamera;

	bool gameInFocus = true;

	glm::vec2 centerOfScreen = glm::vec2(DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2);

	float fireCooldownTime = .1f;
	double nextFireTime = 0.0f;

	std::vector<Entity*> bulletList;
};

