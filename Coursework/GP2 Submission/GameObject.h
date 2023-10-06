#pragma once
#include "transform.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"

class GameObject
{
public:
	GameObject(const std::string& meshPath);
	~GameObject();
private:
	Transform transform;
	Mesh mesh;
	Shader shader;
	Texture texture;
};

