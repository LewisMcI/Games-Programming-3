#include "Scene.h"
#include "Entity.h"
#include "../Camera.h"
#include "../Components/MeshComponent.h"
#include "../Components/TransformComponent.h"
#include "../Components/MaterialComponent.h"
#include "../Components/TagComponent.h"

Scene::Scene(){
	//m_Registry.on_construct<MeshComponent>().connect<&MeshComponent::OnMeshComponentConstruct>();
}
Scene::~Scene() {

}
void Scene::onUpdate(Camera& activeCamera)
{
	drawAllMeshComponents(activeCamera);
}

void Scene::drawAllMeshComponents(Camera& activeCamera) {
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

		material.Bind(transform, activeCamera);

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