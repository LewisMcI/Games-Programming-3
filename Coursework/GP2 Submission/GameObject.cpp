#include "GameObject.h"


GameObject::GameObject(const std::string& meshPath)
{
	// Mesh
	mesh.loadModel(meshPath);
	// Transform
	transform.SetPos(glm::vec3(0.0f, 0.0f, 0.0f));
	transform.SetRot(glm::vec3(0.0f, 0.0f, 0.0f));
	transform.SetScale(glm::vec3(1.0f, 1.0f, 1.0f));
	// Shader
	shader.initShader("..\\Resources\\Shaders\\DefaultShader.vert", "..\\Resources\\Shaders\\DefaultShader.frag");
	// Texture
	texture.initTexture("..\\Resources\\Textures\\Bricks\\DefaultTexture.png");
}

GameObject::~GameObject()
{
	mesh.~Mesh();
	shader.~Shader();
	texture.~Texture();
}
