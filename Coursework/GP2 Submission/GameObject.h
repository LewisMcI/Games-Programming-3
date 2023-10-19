#pragma once
#include "transform.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"

enum class ShaderType { Default, EnviromentMapping };
enum class MeshType { Cube, Draven };
enum class TextureType { Default, Brick };
class GameObject
{
public:
	void init(MeshType meshType = MeshType::Cube,
		ShaderType shaderType = ShaderType::Default,
		TextureType textureType = TextureType::Default);

	void Draw(Camera& camera);

	void linkShader(Camera& camera);
private:
	Transform transform;
	Mesh mesh;
	Shader shader;
	Texture texture;

	MeshType objMeshType;
	ShaderType objShaderType;
	TextureType objTextureType;
};