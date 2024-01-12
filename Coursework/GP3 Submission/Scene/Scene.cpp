#include "Scene.h"
#include "../Components/Collider.h"
#include "../Components/AsteroidMovement.h"
#include "../AudioManager.h"
Scene::Scene(){
	sceneSkybox = std::make_unique<Skybox>();
	Entity& obj = CreateEntity();
}

void Scene::onUpdate() {
	eventSystem.notify<OnUpdateEvent>();
	checkCollisions();
}

void Scene::checkCollisions() {
	// Get all Colliders
	auto view = registry.view<Collider, TransformComponent>();
	for (const auto& entity : view) {
		Collider& collider = view.get<Collider>(entity);
		TransformComponent& transform = view.get<TransformComponent>(entity);
		for (const auto& entity2 : view) {
			if (entity == entity2)
				continue;

			Collider& collider2 = view.get<Collider>(entity2);
			TransformComponent& transform2 = view.get<TransformComponent>(entity2);

			// Ignore Laser Collisions with Player
			Entity* entity = transform.entity.get();
			std::string tag = entity->GetComponent<TagComponent>().Tag;

			Entity* entity2 = transform2.entity.get();
			std::string tag2 = entity2->GetComponent<TagComponent>().Tag;

			if ((tag == "Player" || tag2 == "Player") && (tag == "Laser" || tag2 == "Laser")) {
				continue;
			}
			// Ignore Laser collision
			if (tag == "Laser" && tag2 == "Laser") {
				continue;
			}

			// AABB Collision Detection
			float minX = transform.getPos()->x - collider.size.x;
			float maxX = transform.getPos()->x + collider.size.x;
			float minX2 = transform2.getPos()->x - collider2.size.x;
			float maxX2 = transform2.getPos()->x + collider2.size.x;

			bool collisionX = minX <= maxX2 && maxX >= minX2;
			if (!collisionX)
				continue;

			float minY = transform.getPos()->y - collider.size.y;
			float maxY = transform.getPos()->y + collider.size.y;
			float minY2 = transform2.getPos()->y - collider2.size.y;
			float maxY2 = transform2.getPos()->y + collider2.size.y;

			bool collisionY = minY <= maxY2 && maxY >= minY2;
			if (!collisionY)
				continue;

			float minZ = transform.getPos()->z - collider.size.z;
			float maxZ = transform.getPos()->z + collider.size.z;
			float minZ2 = transform2.getPos()->z - collider2.size.z;
			float maxZ2 = transform2.getPos()->z + collider2.size.z;

			bool collisionZ = minZ <= maxZ2 && maxZ >= minZ2;
			if (!collisionZ)
				continue;

			

			// Collided
			resolveCollision(transform.entity.get());
			resolveCollision(transform2.entity.get());
		}
	}
}

void Scene::resolveCollision(Entity* entity)
{
	std::string tag = entity->GetComponent<TagComponent>().Tag;

	// Player onCollision
	if (tag == "Player") {
		
	}
	// Asteroid onCollision
	else if (tag == "Asteroid") {
		if (entity->HasComponent<Collider>())
			entity->RemoveComponent<Collider>();
		if (entity->HasComponent<MeshComponent>())
			entity->RemoveComponent<MeshComponent>();

		AudioManager::getInstance().playSFX(AudioType::Explosion);
	}
	// Laser onCollision
	else if (tag == "Laser") {
		if (entity->HasComponent<Collider>())
			entity->RemoveComponent<Collider>();
		if (entity->HasComponent<MeshComponent>())
			entity->RemoveComponent<MeshComponent>();
		if (entity->HasComponent<AsteroidMovement>())
			entity->GetComponent<AsteroidMovement>().objectDestroyed = true;
	}
	// Default onCollision
	else {
		if (USE_WARNING_DEBUGGING)
			std::cout << "Warning: Object collided without defined tag, its tag was: " << tag << std::endl;
	}
}

void Scene::draw()
{
	if (activeCamera == nullptr)
		return;
	drawAllMeshComponents();
	sceneSkybox.get()->draw(activeCamera);
}

void Scene::drawAllMeshComponents() {
	// Get and call draw on mesh's
	auto view = registry.view<MeshComponent>();

	for (const auto& entity : view) {
		MeshComponent& mesh = view.get<MeshComponent>(entity);

		// If transform does not exist, add default transform component
		if (!registry.all_of<TransformComponent>(entity)) {
			TransformComponent& transform = registry.emplace<TransformComponent>(entity);
			if (USE_WARNING_DEBUGGING)
				std::cout << "DEBUG: Replaced missing transform with default.";
		}
		TransformComponent& transform = registry.get<TransformComponent>(entity);

		// If material does not exist, add default material component
		if (!registry.all_of<MaterialComponent>(entity)) {
			MaterialComponent& material = registry.emplace<MaterialComponent>(entity);
			if (USE_WARNING_DEBUGGING)
				std::cout << "DEBUG: Replaced missing material with default.";
		}
		MaterialComponent& material = registry.get<MaterialComponent>(entity);

		material.Bind(transform, *activeCamera);

		mesh.Draw();
	}
}

Entity Scene::CreateEntity(const std::string& name, glm::vec3 pos)
{
	Entity entity = { registry.create(), this };
	entity.AddComponent<TransformComponent>(pos);
	auto& tag = entity.AddComponent<TagComponent>();
	tag.Tag = name.empty() ? "Entity" : name;
	return entity;
}