#pragma once
#include "transform.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"

class GameObject
{
public:
	GameObject(Camera& camera) : camera(camera){

	}

	void init(std::string meshName, Shader objectShader, std::string textureName);

	void Draw();
private:
	Transform transform;

	Mesh mesh;
	Shader shader;
	Texture texture;

	Camera& camera;
};

