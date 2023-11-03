#pragma once
#include "Shader.h"
#include "Texture.h"

enum class ShaderType { Default, EnviromentMapping };
enum class TextureType { Default, Brick };
class MaterialComponent {
public:
	MaterialComponent(ShaderType shaderType = ShaderType::Default, TextureType textureType = TextureType::Default);

	void Bind(TransformComponent& transform, Camera& camera);
protected:
private:
	Shader associatedShader;
	Texture associatedTexture;

};