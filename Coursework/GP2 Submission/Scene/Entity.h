#pragma once
#include "entt\entt.hpp"
#include "../Other/GlobalVariables.h"

/*Forward Declaration to prevent Circular Includes*/
class Scene;

// Check if a type has a method onUpdate
template <typename T>
struct has_onUpdate {
	// Substitution Failure is Not An Error (SFINAE) test
	template <typename C>
	// Attempt to call the onUpdate method on an instance of type C
	static constexpr auto test(int) -> decltype(std::declval<C>().onUpdate(), std::true_type{});

	// Fallback
	template <typename>
	// This is a fallback for when the SFINAE test fails (Substitution Failure)
	static constexpr std::false_type test(...);

	// The result of the test is stored in the 'value' member
	static constexpr bool value = decltype(test<T>(0))::value;
};

class Entity {
public:
	Entity::Entity(entt::entity handle, Scene* scene)
		: entityHandle(handle), entityScene(scene) {
	}
	/* Copy Constructor*/
	Entity(const Entity& other) : entityHandle(other.entityHandle), entityScene(other.entityScene){

	}

	~Entity() {
		
	}

	/* Variatic Template
	* Takes all values and passes them along without unpacking.
	*/
	template <typename T, typename... Args>
	T& AddComponent(Args&&... args) {
		// Check if Entity already has Component (Debugging purposes)
		if (HasComponent<T>() && USE_WARNING_DEBUGGING)
			std::cout << "Debug: Trying to Add Component that already exists" << std::endl;

		// Create and Add Component
		auto& component = entityScene->registry.emplace<T>(entityHandle, std::forward<Args>(args)...);
		// If T has method onUpdate
		if constexpr (has_onUpdate<T>::value) {
			// Subscribe the onUpdate method to the onUpdateEvent
			entityScene->subscribeUpdate([&component]() {
				component.onUpdate();
				});
		}

		// If component is, or extends Component
		if constexpr (std::is_base_of_v<Component, T>) {
			component.entity = std::make_shared<Entity>(entityHandle, entityScene);
		}

		return component;
	}

	template<typename T>
	T& GetComponent() {
		if (!HasComponent<T>() && USE_WARNING_DEBUGGING)
			std::cout << "Debug: Trying to Get Component that does not exist" << std::endl;

		return entityScene->registry.get<T>(entityHandle);
	}

	template<typename T>
	bool HasComponent() {
		bool hasComponent = entityScene->registry.all_of<T>(entityHandle);
		return hasComponent;
	}

	template<typename T>
	bool RemoveComponent() {
		if (!HasComponent<T>() && USE_WARNING_DEBUGGING)
			std::cout << "Trying to Remove Component that does not exist";
		return entityScene->registry.remove<T>(entityHandle);
	}
	entt::entity entityHandle = entt::null;
protected:
private:
	Scene* entityScene = nullptr;
};
