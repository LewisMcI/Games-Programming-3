#pragma once
#define SDL_MAIN_HANDLED 
#include "Camera.h"
#include <SDL2/SDL_events.h>

class PlayerController
{
public:
	PlayerController();
	~PlayerController();

	void init(Camera* camera, TransformComponent* transform);

	void processInput();

	void processKeyboardInput(const Uint8* keys);

	void processMouseInput(SDL_MouseMotionEvent* event);

protected:
private:

	TransformComponent* playerTransform;

	Camera* playerCamera;
};

