#include "Scene.h"
#include "../Components/Collider.h"

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

			float maxX = transform.getPos()->x + collider.size.x;
			float maxY = transform.getPos()->y + collider.size.y;
			float maxZ = transform.getPos()->z + collider.size.z;

			float maxX2 = transform2.getPos()->x + collider2.size.x;
			float maxY2 = transform2.getPos()->y + collider2.size.y;
			float maxZ2 = transform2.getPos()->z + collider2.size.z;

			float minX = transform.getPos()->x - collider.size.x;
			float minY = transform.getPos()->y - collider.size.y;
			float minZ = transform.getPos()->z - collider.size.z;

			float minX2 = transform2.getPos()->x - collider2.size.x;
			float minY2 = transform2.getPos()->y - collider2.size.y;
			float minZ2 = transform2.getPos()->z - collider2.size.z;

			bool collisionX = minX <= maxX2 && maxX >= minX2;

			bool collisionY = minY <= maxY2 && maxY >= minY2;

			bool collisionZ = minZ <= maxZ2 && maxZ >= minZ2;

			// Collided
			if (collisionX && collisionY && collisionZ)
			{
				if (transform.entity.get()->GetComponent<TagComponent>().Tag == "Player") {

				}
				else if (transform.entity.get()->GetComponent<TagComponent>().Tag == "Asteroid") {
					transform.entity.get()->~Entity();
					std::cout << "destructed" << std::endl;
				}
			}

		}
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
			std::cout << "DEBUG: Replaced missing transform with default.";
		}
		TransformComponent& transform = registry.get<TransformComponent>(entity);

		// If material does not exist, add default material component
		if (!registry.all_of<MaterialComponent>(entity)) {
			MaterialComponent& material = registry.emplace<MaterialComponent>(entity);
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