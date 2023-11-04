#pragma once
#include "entt\entt.hpp"
#include <glm\glm.hpp>
#include "..\Camera.h"
class Entity;

class Scene
{
public:
	Scene();
	~Scene();

	Entity CreateEntity(const std::string& name = "");

	void onUpdate(Camera& activeCamera);
	
private:
	entt::registry registry;

	friend class Entity;
};

