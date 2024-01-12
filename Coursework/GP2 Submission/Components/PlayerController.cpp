#pragma once
#include "PlayerController.h"
#include "../AudioManager.h"
#include "Player.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneManager.h"
#include "Collider.h"
#include "Bullet.h"

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
	SDL_WarpMouseInWindow(SDL_GL_GetCurrentWindow(), static_cast<int>(centerOfScreen.x), static_cast<int>(centerOfScreen.y));
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
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDL_KeyCode::SDLK_c) { // Move right
				Player& playerComp = playerTransform->entity.get()->GetComponent<Player>();
				switch (playerComp.cameraState) {
				case CameraState::FirstPerson:
					playerComp.cameraState = CameraState::ThirdPerson;
					break;
				case CameraState::ThirdPerson:
					playerComp.cameraState = CameraState::FirstPerson;
					break;
				}
			}
			break;
		case SDL_WINDOWEVENT:
			if (event.window.event == SDL_WINDOWEVENT_FOCUS_LOST) {
				gameInFocus = false;
			}
			else if (event.window.event == SDL_WINDOWEVENT_FOCUS_GAINED) {
				gameInFocus = true;
			}
			break;
			// OnMouseMove - Handles mouse movement to control camera.
		case SDL_MOUSEBUTTONDOWN:
			break;
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
	if (keys[SDL_SCANCODE_D]) { // Rotate left
		playerTransform->rotate(-forward * rotationSpeed);
	}

	int mouseX, mouseY;
	Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);
	if (keys[SDL_SCANCODE_SPACE] || (mouseState && SDL_BUTTON(SDL_BUTTON_LEFT) != 0)){ // Fire
		if (nextFireTime > Time::getInstance().getCurrentTime())
			return;
		nextFireTime = Time::getInstance().getCurrentTime() + fireCooldownTime;
		shootBullet(playerCamera->getPos() - (playerCamera->getRight() * 6.0f));
		shootBullet(playerCamera->getPos() + (playerCamera->getRight() * 6.0f));
	}

	// Delete old bullets
	auto it = bulletList.begin();
	while (it != bulletList.end()) {
		Entity* entity = *it;
		Bullet& bullet = entity->GetComponent<Bullet>();

		if (bullet.shouldDelete) {
			entity->RemoveComponent<Collider>();
			entity->RemoveComponent<MeshComponent>();
			entity->RemoveComponent<Bullet>();
			bullet.~Bullet();

			// Remove from bulletList
			it = bulletList.erase(it);
			delete entity;  // Assuming the entity is allocated with new

		}
		else {
			++it;
		}
	}
}

void PlayerController::shootBullet(glm::vec3 pos) {
	AudioManager::getInstance().playSFX(AudioType::Fire);

	// Spawn Left
	auto& activeScene = SceneManager::getInstance().getActiveScene();

	Entity* bullet = new Entity(activeScene.get()->CreateEntity("Laser", pos));

	bullet->AddComponent<MaterialComponent>(ShaderType::EnviromentMapping, TextureType::Laser);

	bullet->AddComponent<MeshComponent>(MeshType::Laser);

	bullet->AddComponent<Collider>(glm::vec3(20.0f));

	bullet->GetComponent<TagComponent>().Tag = "Laser";

	bullet->AddComponent<Bullet>(bullet->GetComponent<TransformComponent>(), playerCamera->getForward());
	bulletList.emplace_back(bullet);
}

void PlayerController::processMouseInput() {
	// Current Point
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	glm::vec2 currentPoint = glm::vec2(mouseX, mouseY);

	// Distance to Center
	glm::vec2 distanceToCenter = centerOfScreen - currentPoint;

	// Calculate Speed
	float speedX = (distanceToCenter.x / DISPLAY_WIDTH * 300.0f) * 0.01f * Time::getInstance().getDeltaTime();
	float speedY = (distanceToCenter.y / DISPLAY_WIDTH * 300.0f) * 0.01f * Time::getInstance().getDeltaTime();

	glm::vec3 right = playerCamera->getRight();
	glm::vec3 up = playerCamera->getUp();

	playerTransform->rotate(right * speedY);
	playerTransform->rotate(up * speedX);
}