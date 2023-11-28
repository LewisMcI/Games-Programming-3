#pragma once
#include "PlayerController.h"
#include <iostream>
#include "Time.h"

PlayerController::PlayerController()
{
}

PlayerController::~PlayerController()
{
}

void PlayerController::init(Camera* camera, TransformComponent* transform)
{
	playerCamera = camera;
	playerTransform = transform;
}

void PlayerController::processInput()
{
	// Creates new Event.
	SDL_Event event;
	// While events are still coming in.
	while (SDL_PollEvent(&event))
	{
		// Switch statement
		switch (event.type)
		{
			// Quit
		case SDL_QUIT:
			//gameState = GameState::EXIT;
			break;
			// OnMouseMove - Handles mouse movement to control camera.
		case SDL_MOUSEMOTION:
			processMouseInput(&event.motion);
			break;
		default:
			break;
		}
	}
	const Uint8* keys = SDL_GetKeyboardState(NULL);
	processKeyboardInput(keys);
}

void PlayerController::processKeyboardInput(const Uint8* keys)
{
	float distance = 40.0f * Time::getInstance().getDeltaTime();

	if (keys[SDL_SCANCODE_W]) { // Move forward
		playerTransform->moveZ(distance);
	}
	if (keys[SDL_SCANCODE_S]) { // Move backward
		playerTransform->moveZ(-distance);
	}
	if (keys[SDL_SCANCODE_A]) { // Move left
		playerTransform->moveX(distance);
	}
	if (keys[SDL_SCANCODE_D]) { // Move right
		playerTransform->moveX(-distance);
	}
	if (keys[SDL_SCANCODE_SPACE]) {
		playerTransform->moveY(distance);
	}
	if (keys[SDL_SCANCODE_LSHIFT]) {
		playerTransform->moveY(-distance);
	}
}

void PlayerController::processMouseInput(SDL_MouseMotionEvent* event)
{	
	// Rotates X by the relative X value given through the cursor. (Must be inverted)
	//playerTransform->rotateX(-event->xrel * 0.001f);
	// Rotates Y by the relative Y value given through the cursor.
	//playerTransform->rotateY(event->yrel * 0.001f);
}
