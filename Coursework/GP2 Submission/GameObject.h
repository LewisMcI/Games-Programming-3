#pragma once
#include "transform.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"

class GameObject
{
public:
	void init(std::string meshName, std::string fragShader, std::string vertexShader, std::string textureName);

	void Draw(Camera& camera);
private:
	Transform transform;

	Mesh mesh;
	Shader shader;
	Texture texture;

};

