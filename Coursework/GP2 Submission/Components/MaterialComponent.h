#pragma once
#include "../Base Scripts/Shader.h"
#include "../Base Scripts/TextureLoader.h"

enum class ShaderType { Default, EnviromentMapping };

class MaterialComponent : public Component {
public:

	MaterialComponent(ShaderType shaderType = ShaderType::Default, TextureType textureType = TextureType::Default)
		: associatedShaderType(shaderType), associatedTextureType(textureType), textureLoader(TextureLoader::getInstance())
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