#include "Scene.h"
#include "Entity.h"
#include "../Components/Component.h"


Scene::Scene(){
	sceneSkybox = std::make_unique<Skybox>();
	Entity& obj = CreateEntity();
}

void Scene::onUpdate() {
	eventSystem.notify<OnUpdateEvent>();
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

Entity Scene::CreateEntity(const std::string& name)
{
	Entity entity = { registry.create(), this };
	entity.AddComponent<TransformComponent>();
	auto& tag = entity.AddComponent<TagComponent>();
	tag.Tag = name.empty() ? "Entity" : name;
	return entity;
}