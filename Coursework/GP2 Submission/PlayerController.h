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

	void processKeyboardInput(const Uint8* keys);

	void processMouseInput(SDL_MouseMotionEvent* event);

protected:
private:

	Camera* playerCamera;
};

