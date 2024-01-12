#pragma once
#define SDL_MAIN_HANDLED 
#include "../Base Scripts/Camera.h"
#include <SDL2/SDL_events.h>
#include <iostream>
#include "../Base Scripts/Time.h"

class PlayerController
{
public:
	PlayerController();
	~PlayerController();

	void init(Camera* camera, TransformComponent* transform);

	void processInput();

	void processKeyboardInput(const Uint8* keys);

	void processMouseInput();

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

