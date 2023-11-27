#pragma once
#include "entt\entt.hpp"
#include <glm\glm.hpp>
#include "..\Camera.h"
#include "../SkyBox.h"
class Entity;

class Scene
{
public:
	Scene();
	~Scene();

	Entity CreateEntity(const std::string& name = "");

	void onUpdate(Camera& activeCamera);
	
private:
	void drawAllMeshComponents(Camera& activeCamera);

	entt::registry registry;

	std::unique_ptr<Skybox> sceneSkybox;

	friend class Entity;
};

