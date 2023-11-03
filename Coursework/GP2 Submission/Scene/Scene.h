#pragma once
#include "entt\entt.hpp"
#include "../MaterialComponent.h"
#include "../TransformComponent.h"
#include "../MeshComponent.h"

class Scene
{
public:
	Scene();
	~Scene();

	entt::entity CreateEntity();

	// TEMP
	entt::registry& Reg() { return m_Registry; }

	void onUpdate(Camera& activeCamera);
	
private:
	entt::registry m_Registry;
};

