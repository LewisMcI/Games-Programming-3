#pragma once
#include "entt\entt.hpp"
#include "Scene.h"

class Entity {
public:
	Entity(entt::entity handle, Scene* scene);
	Entity(const Entity& other) = default;

	/* Variatic Template
	* Takes all values and passes them along without unpacking.
	*/
	template <typename T, typename... Args>
	T& AddComponent(Args&&... args){
		if (HasComponent<T>())
			std::cout << "Debug: Trying to Add Component that already exists";

		return entityScene->registry.emplace<T>(entityHandle, std::forward<Args>(args)...);
	}

	template<typename T>
	T& GetComponent() {
		if (!HasComponent<T>())
			std::cout << "Debug: Trying to Get Component that does not exist";

		return entityScene->registry.get<T>(entityHandle);
	}

	template<typename T>
	bool HasComponent() {
		return entityScene->registry.all_of<T>(entityHandle);
	}

	template<typename T>
	bool RemoveComponent() {
		if (!HasComponent<T>())
			std::cout << "Debug: Trying to Remove Component that does not exist";
		entityScene->registry.remove<T>(entityHandle);
	}
protected:
private:
	entt::entity entityHandle = entt::null;
	Scene* entityScene = nullptr;
};
