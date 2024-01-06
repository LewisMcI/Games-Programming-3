#pragma once
#include "entt\entt.hpp"
#include "Scene.h"
// Check if a type has a member function called onUpdate
template <typename T>
struct has_onUpdate {
	// SFINAE test
	template <typename C>
	static constexpr auto test(int) -> decltype(std::declval<C>().onUpdate(), std::true_type{});

	// Fallback
	template <typename>
	static constexpr std::false_type test(...);

	static constexpr bool value = decltype(test<T>(0))::value;
};

class Entity {
public:
	Entity(entt::entity handle, Scene* scene);
	Entity(const Entity& other) = default;

	/* Variatic Template
	* Takes all values and passes them along without unpacking.
	*/
	template <typename T, typename... Args>
	T& AddComponent(Args&&... args) {
		// Check if Entity already has Component (Debugging purposes)
		if (HasComponent<T>())
			std::cout << "Debug: Trying to Add Component that already exists";

		// Create and Add Component
		auto& component = entityScene->registry.emplace<T>(entityHandle, std::forward<Args>(args)...);
		// Check if the new component has an onUpdate function
		if constexpr (has_onUpdate<T>::value) {
			// Subscribe the onUpdate method to the onUpdateEvent
			entityScene->subscribeUpdate([&component]() {
				component.onUpdate();
				});
		}
		return component;
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
