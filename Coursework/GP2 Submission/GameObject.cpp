#include "GameObject.h"

void GameObject::init(std::string meshName, Shader objectShader, std::string textureName)
{
	mesh.loadModel(meshName);
	texture.initTexture(textureName);
	shader = objectShader;
}

void GameObject::Draw(){
	transform.SetPos(glm::vec3(0.0f, 0.0f, 5.0f));
	transform.SetRot(glm::vec3(0.0f, 0.0f, 0.0f));
	transform.SetScale(glm::vec3(1.0f, 1.0f, 1.0f));

	shader.Bind();
	shader.Update(transform, camera);
	texture.Bind(0);

	mesh.Draw();
}
