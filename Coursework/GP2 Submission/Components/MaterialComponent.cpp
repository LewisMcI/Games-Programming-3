#include "MaterialComponent.h"

void MaterialComponent::LoadMaterial()
{
	switch (associatedShaderType) {
	case ShaderType::Default:
		associatedShader.initShader("..\\Resources\\Shaders\\DefaultShader.vert", "..\\Resources\\Shaders\\DefaultShader.frag");
		break;
	case ShaderType::EnviromentMapping:
		associatedShader.initShader("..\\Resources\\Shaders\\EnvironmentMapping.vert", "..\\Resources\\Shaders\\EnvironmentMapping.frag");
		break;
	}
	textureLoader.initTexture(associatedTextureType);
}

void MaterialComponent::Bind(TransformComponent& transform, Camera& camera)
{
	associatedShader.Bind();
	associatedShader.Update(transform, camera);

	textureLoader.Bind(associatedTextureType, 0);
	LinkShader(transform, camera);
}

void MaterialComponent::LinkShader(TransformComponent& transform, Camera& camera)
{
	switch (associatedShaderType) {
	case ShaderType::Default:
		break;
	case ShaderType::EnviromentMapping:
		glm::mat4 model = transform.GetModel();

		glm::mat4 view = camera.GetViewProjection();

		glm::mat4 modelView = view * model;
		associatedShader.setVec3("camPos", camera.getPos());
		associatedShader.setFloat("reflectiveness", .75f);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		associatedShader.setMat4("model", transform.GetModel());
		associatedShader.setMat4("transform", modelView);
		GLuint diffuseTexLocation = glGetUniformLocation(associatedShader.getId(), "diffuse");
		GLuint skyboxTexLocation = glGetUniformLocation(associatedShader.getId(), "skybox");

		glUniform1i(diffuseTexLocation, 1);
		glUniform1i(skyboxTexLocation, 0);

		glActiveTexture(GL_TEXTURE0 + 1);
		glBindTexture(GL_TEXTURE_2D, textureLoader.getID(associatedTextureType));
		break;
	}
}
