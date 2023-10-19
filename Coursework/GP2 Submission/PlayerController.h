#pragma once
#include "Camera.h"
#include <SDL/SDL_events.h>

class PlayerController
{
public:
	PlayerController();
	~PlayerController();

	void init(Camera* camera);

	void processInput();

	void processKeyboardInput(SDL_Keysym* keySym);

	void processMouseInput(SDL_MouseMotionEvent* event);

protected:
private:

	Camera* playerCamera;
};

