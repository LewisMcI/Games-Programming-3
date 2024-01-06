#pragma once
#include "entt\entt.hpp"
#include <glm\glm.hpp>
#include "..\Camera.h"
#include "..\SkyBox.h"
#include "..\Camera.h"
#include "..\Components\MeshComponent.h"
#include "..\Components\TransformComponent.h"
#include "..\Components\MaterialComponent.h"
#include "..\Components\TagComponent.h"
#include "../Other/EventSystem.h"
class Entity;

class Scene
{
public:
	Scene();
	~Scene() {
		sceneSkybox.reset();
	};

	void onUpdate();

	void draw();

	Entity CreateEntity(const std::string& name = "");
	
	void subscribeUpdate(std::function<void()> callback) {
		eventSystem.subscribe<OnUpdateEvent>(callback);
	}

	void changeActiveCamera(Camera& camera) {
		activeCamera = &camera;
	}

private:
	void drawAllMeshComponents();

	entt::registry registry;

	std::unique_ptr<Skybox> sceneSkybox;

	Camera* activeCamera;

	friend class Entity;

	EventSystem eventSystem;
};

