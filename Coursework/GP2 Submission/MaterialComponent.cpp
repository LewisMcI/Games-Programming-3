#include "MaterialComponent.h"

MaterialComponent::MaterialComponent(ShaderType shaderType, TextureType textureType)
{
	switch (shaderType) {
		case ShaderType::Default:
			associatedShader.initShader("..\\Resources\\Shaders\\DefaultShader.vert", "..\\Resources\\Shaders\\DefaultShader.frag");
			break;
		case ShaderType::EnviromentMapping:
			associatedShader.initShader("..\\Resources\\Shaders\\EnvironmentMapping.vert", "..\\Resources\\Shaders\\EnvironmentMapping.frag");
			break;
	}
	switch (textureType) {		
		case TextureType::Default:
			associatedTexture.initTexture("..\\Resources\\Textures\\DefaultTexture.jpg");
			break;
		case TextureType::Brick:
			associatedTexture.initTexture("..\\Resources\\Textures\\Bricks\\BrickAlbedo.png");
			break;
	}
}

void MaterialComponent::Bind(TransformComponent& transform, Camera& camera)
{
	associatedShader.Bind();
	associatedShader.Update(transform, camera);

	associatedTexture.Bind(0);
}
