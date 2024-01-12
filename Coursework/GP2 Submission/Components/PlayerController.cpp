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
	SDL_Surface* cursorSurface = SDL_CreateRGBSurface(0, 2, 2, 32, 0, 0, 0, 0);
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
	Player& playerComp = playerTransform->entity.get()->GetComponent<Player>();
	switch (playerComp.cameraState) {
	case CameraState::FirstPerson:
		SDL_ShowCursor(SDL_ENABLE);
		SDL_SetRelativeMouseMode(SDL_FALSE);
		break;
	case CameraState::ThirdPerson:
		SDL_ShowCursor(SDL_ENABLE);
		SDL_SetRelativeMouseMode(SDL_FALSE);
		break;
	case CameraState::FreeCam:
		SDL_ShowCursor(SDL_DISABLE);
		SDL_SetRelativeMouseMode(SDL_TRUE);
		break;
	}
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
					SDL_WarpMouseInWindow(SDL_GL_GetCurrentWindow(), static_cast<int>(centerOfScreen.x), static_cast<int>(centerOfScreen.y));
					playerComp.cameraState = CameraState::ThirdPerson;
					break;
				case CameraState::ThirdPerson:
					SDL_ShowCursor(SDL_DISABLE);
					SDL_SetRelativeMouseMode(SDL_TRUE); // Confine the cursor to the window
					SDL_WarpMouseInWindow(SDL_GL_GetCurrentWindow(), static_cast<int>(centerOfScreen.x), static_cast<int>(centerOfScreen.y));
					playerComp.cameraState = CameraState::FreeCam;
					break;
				case CameraState::FreeCam:
					SDL_ShowCursor(SDL_ENABLE);
					SDL_SetRelativeMouseMode(SDL_FALSE); // Confine the cursor to the window
					SDL_WarpMouseInWindow(SDL_GL_GetCurrentWindow(), static_cast<int>(centerOfScreen.x), static_cast<int>(centerOfScreen.y));
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
	Player& playerComp = playerTransform->entity.get()->GetComponent<Player>();
	switch (playerComp.cameraState) {
	case CameraState::ThirdPerson:
	case CameraState::FirstPerson:
		processKeyboardInput(keys);
		processMouseInput();
		break;
	case CameraState::FreeCam:
		processFreecamKeyboardInput(keys);
		processFreecamMouseInput();
		break;
	}
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
	if (keys[SDL_SCANCODE_A]) { // Rotate left
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
		nextFireTime = Time::getInstance().getCurrentTime() + (fireCooldownTime / TIME_STEP);
		shootBullet(playerCamera->getPos() - (playerCamera->getRight() * 6.0f));
		shootBullet(playerCamera->getPos() + (playerCamera->getRight() * 6.0f));
	}

	// Delete old bullets
	auto it = bulletList.begin();
	while (it != bulletList.end()) {
		Entity* entity = *it;
		Bullet& bullet = entity->GetComponent<Bullet>();

		if (bullet.shouldDelete) {
			if (entity->HasComponent<Collider>())
				entity->RemoveComponent<Collider>();
			if (entity->HasComponent<MeshComponent>())
				entity->RemoveComponent<MeshComponent>();
			if (entity->HasComponent<Bullet>())
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

	bullet->AddComponent<Collider>(glm::vec3(1.0f));

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
	float speedY = (distanceToCenter.y / DISPLAY_HEIGHT * 300.0f) * 0.01f * Time::getInstance().getDeltaTime();

	glm::vec3 right = glm::vec3(-1, 0, 0);
	glm::vec3 up = glm::vec3(0,1,0);
	
	std::cout << playerTransform->getRight().x << " " << playerTransform->getRight().y << playerTransform->getRight().z << std::endl;

	playerTransform->rotate(up * speedX);
	playerTransform->rotate(right * speedY);
	//playerTransform->rotate(forward * speedX);

}

void PlayerController::processFreecamInput() {

	const Uint8* keys = SDL_GetKeyboardState(NULL);
	processFreecamKeyboardInput(keys);
}

void PlayerController::processFreecamKeyboardInput(const Uint8* keys)
{
	float moveDistance = 200.0f * Time::getInstance().getDeltaTime();

	if (keys[SDL_SCANCODE_W]) { // Move Forward
		playerCamera->MoveForward(moveDistance);
	}
	if (keys[SDL_SCANCODE_S]) { // Move Backward
		playerCamera->MoveForward(-moveDistance);
	}
	if (keys[SDL_SCANCODE_A]) { // Rotate left
		playerCamera->MoveLeft(moveDistance);
	}
	if (keys[SDL_SCANCODE_D]) { // Rotate left
		playerCamera->MoveLeft(-moveDistance);
	}
}
void PlayerController::processFreecamMouseInput() {
	// Current Point
	int mouseX, mouseY;
	SDL_GetRelativeMouseState(&mouseX, &mouseY);
	float rotationSpeed = 2.0f * Time::getInstance().getDeltaTime();

	// Rotates X by the relative X value given through the cursor. (Must be inverted)
	playerCamera->RotateX(-mouseX * rotationSpeed);
	// Rotates Y by the relative Y value given through the cursor.
	playerCamera->RotateY(mouseY * rotationSpeed);
}