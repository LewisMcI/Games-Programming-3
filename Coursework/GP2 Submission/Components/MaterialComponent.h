#pragma once
#include "../Shader.h"
#include "../TextureLoader.h"

enum class ShaderType { Default, EnviromentMapping };

class MaterialComponent {
public:

	MaterialComponent(ShaderType shaderType = ShaderType::Default, TextureType textureType = TextureType::Default, TextureLoader& textureLoader = TextureLoader())
		: associatedShaderType(shaderType), associatedTextureType(textureType), textureLoader(textureLoader)
	{
		LoadMaterial();
	}

	void LoadMaterial();


	void Bind(TransformComponent& transform, Camera& camera);

	void LinkShader(TransformComponent& transform, Camera& camera);

protected:
private:
	Shader associatedShader;
	TextureLoader& textureLoader;

	ShaderType associatedShaderType{ ShaderType::Default };
	TextureType associatedTextureType{ TextureType::Default };
};