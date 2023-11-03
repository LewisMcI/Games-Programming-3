#include "Scene.h"
#include <glm\glm.hpp>


Scene::Scene(){
	//m_Registry.on_construct<MeshComponent>().connect<&MeshComponent::OnMeshComponentConstruct>();
}
Scene::~Scene() {

}
void Scene::onUpdate(Camera& activeCamera)
{
	// Get and call draw on mesh's
	auto view = m_Registry.view<MeshComponent>();
	for (auto entity : view) {
		MeshComponent& mesh = view.get<MeshComponent>(entity);

		// If transform does not exist, add default transform component
		if (!m_Registry.all_of<TransformComponent>(entity)) {
			TransformComponent& transform = m_Registry.emplace<TransformComponent>(entity);
			std::cout << "DEBUG: Replaced missing transform with default.";
		}
		TransformComponent& transform = m_Registry.get<TransformComponent>(entity);

		// If material does not exist, add default material component
		if (!m_Registry.all_of<MaterialComponent>(entity)) {
			MaterialComponent& material = m_Registry.emplace<MaterialComponent>(entity);
			std::cout << "DEBUG: Replaced missing material with default.";

		}
		MaterialComponent& material = m_Registry.get<MaterialComponent>(entity);
		
		material.Bind(transform, activeCamera);

		mesh.Draw();
	}
}

entt::entity Scene::CreateEntity()
{
	entt::entity entity = m_Registry.create();
	return entity;
}
