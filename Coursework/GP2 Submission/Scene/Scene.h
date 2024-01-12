#pragma once
#include "entt\entt.hpp"
#include <glm\glm.hpp>
#include "../Base Scripts/Camera.h"
#include "../Base Scripts/SkyBox.h"
#include "../Other/EventSystem.h"
#include "..\Components\MeshComponent.h"
#include "..\Components\TransformComponent.h"
#include "..\Components\MaterialComponent.h"
#include "..\Components\TagComponent.h"
#include "Entity.h"

class Scene
{
public:
	Scene();
	~Scene() {
		sceneSkybox.reset();
	};

	void onUpdate();

	void draw();

	Entity CreateEntity(const std::string& name = "", glm::vec3 pos = glm::vec3(0.0f));
	
	void subscribeUpdate(std::function<void()> callback) {
		eventSystem.subscribe<OnUpdateEvent>(callback);
	}

	void changeActiveCamera(Camera& camera) {
		activeCamera = &camera;
	}

private:
	void drawAllMeshComponents();
	
	void checkCollisions();

	void resolveCollision(Entity* entity);

	entt::registry registry;

	std::unique_ptr<Skybox> sceneSkybox;

	Camera* activeCamera;

	friend class Entity;

	EventSystem eventSystem;
};

