#pragma once
#include "PlayerController.h"
#include "../AudioManager.h"


PlayerController::PlayerController() {
	// Create a white cursor
	SDL_Surface* cursorSurface = SDL_CreateRGBSurface(0, 3, 3, 32, 0, 0, 0, 0);
	if (cursorSurface) {
		Uint32 white = SDL_MapRGB(cursorSurface->format, 255, 255, 255);
		SDL_FillRect(cursorSurface, NULL, white);
		SDL_Cursor* cursor = SDL_CreateColorCursor(cursorSurface, 0, 0);
		if (cursor) {
			SDL_SetCursor(cursor);
		}
		SDL_FreeSurface(cursorSurface);
	}
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
		case SDL_WINDOWEVENT:
			if (event.window.event == SDL_WINDOWEVENT_FOCUS_LOST) {
				gameInFocus = false;
			}
			else if (event.window.event == SDL_WINDOWEVENT_FOCUS_GAINED) {
				gameInFocus = true;
			}
			// OnMouseMove - Handles mouse movement to control camera.
		default:
			break;
		}
	}

	const Uint8* keys = SDL_GetKeyboardState(NULL);
	processKeyboardInput(keys);
	processMouseInput();

}

void PlayerController::processKeyboardInput(const Uint8* keys)
{
	float moveDistance = 200.0f * Time::getInstance().getDeltaTime();
	float rotationSpeed = 2.0f * Time::getInstance().getDeltaTime();
	// Calculate Forward
	glm::vec3 forward = playerCamera->getForward();	
	
	if (keys[SDL_SCANCODE_W]) { // Move Forward
		playerTransform->move(forward * moveDistance);
	}
	if (keys[SDL_SCANCODE_S]) { // Move Backward
		playerTransform->move(-forward * moveDistance);
	}
	if (keys[SDL_SCANCODE_D]) { // Rotate left
		playerTransform->rotate(forward * rotationSpeed);
	}
	if (keys[SDL_SCANCODE_A]) { // Move right
		playerTransform->rotate(-forward * rotationSpeed);
	}
	if (keys[SDL_SCANCODE_E]){
		AudioType audioType = AudioType::Fire;
		AudioManager::getInstance().playSFX(audioType);
	}
}

void PlayerController::processMouseInput() {

	// Center Point
	glm::vec2 centerOfScreen = glm::vec2(DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2);

	// Current Point
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	glm::vec2 currentPoint = glm::vec2(mouseX, mouseY);

	// Distance to Center
	glm::vec2 distanceToCenter = centerOfScreen - currentPoint;

	// Calculate Speed
	float speedX = distanceToCenter.x * 0.000001f;
	float speedY = distanceToCenter.y * 0.000001f;

	glm::vec3 right = playerCamera->getRight();
	glm::vec3 up = playerCamera->getUp();

	playerTransform->rotate(right * speedY);
	playerTransform->rotate(up * speedX);
}