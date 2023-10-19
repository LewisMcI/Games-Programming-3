#pragma once
#include "PlayerController.h"
#include <iostream>

PlayerController::PlayerController()
{
}

PlayerController::~PlayerController()
{
}

void PlayerController::init(Camera* camera)
{
	playerCamera = camera;
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
			// OnKeyDown - Handles keyboard input to control camera.
		case SDL_KEYDOWN:
			processKeyboardInput(&event.key.keysym);
			break;
			// OnMouseMove - Handles mouse movement to control camera.
		case SDL_MOUSEMOTION:
			processMouseInput(&event.motion);
			break;
		default:
			break;
		}
	}
}

void PlayerController::processKeyboardInput(SDL_Keysym* keySym)
{
	float distance = 2.0f;
	// Modifiers
	switch (keySym->mod) {
		// Move Faster Key
	case KMOD_LSHIFT:
		distance *= 2.0f;
		break;
		// Move Slower Key
	case KMOD_LCTRL:
		distance *= 0.25f;
		break;
	}
	// Movement Keys
	switch (keySym->sym) {
		// Forward Key
	case SDLK_UP:
	case SDLK_w:
		playerCamera->MoveX(distance);
		break;
		// Backward Key
	case SDLK_DOWN:
	case SDLK_s:
		playerCamera->MoveX(-distance);
		break;
		// Left Key
	case SDLK_LEFT:
	case SDLK_a:
		playerCamera->MoveZ(distance);
		break;
		// Right Key
	case SDLK_RIGHT:
	case SDLK_d:
		playerCamera->MoveZ(-distance);
		break;
		// Up Key
	case SDLK_SPACE:
		playerCamera->MoveY(distance);
		break;
	}
}

void PlayerController::processMouseInput(SDL_MouseMotionEvent* event)
{	
	// Rotates X by the relative X value given through the cursor. (Must be inverted)
	playerCamera->RotateX(-event->xrel * 0.001f);
	// Rotates Y by the relative Y value given through the cursor.
	playerCamera->RotateY(event->yrel * 0.001f);
}
