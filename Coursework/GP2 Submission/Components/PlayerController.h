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
	TransformComponent* playerTransform;

	Camera* playerCamera;

	bool gameInFocus = true;
};

