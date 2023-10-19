#include "GameObject.h"

void GameObject::init(MeshType meshType, ShaderType shaderType, TextureType textureType)
{
	this->objShaderType = shaderType;
	this->objTextureType = textureType;
	switch (meshType) {
		case MeshType::Cube:
			mesh.loadModel("..\\Resources\\Models\\Cube.obj");
			break;
		case MeshType::Draven:
			mesh.loadModel("..\\Resources\\Models\\draven.obj");
			break;
	}
	switch (objShaderType) {
		case ShaderType::Default:
			shader.initShader("..\\Resources\\Shaders\\DefaultShader.vert", "..\\Resources\\Shaders\\DefaultShader.frag");
			break;
		case ShaderType::EnviromentMapping:
			shader.initShader("..\\Resources\\Shaders\\EnvironmentMapping.vert", "..\\Resources\\Shaders\\EnvironmentMapping.frag");
			break;
	}
	switch (textureType) {
		case TextureType::Default:
			texture.initTexture("..\\Resources\\Textures\\DefaultTexture.jpg");
			break;
		case TextureType::Brick:
			texture.initTexture("..\\Resources\\Textures\\Bricks\\BrickAlbedo.png");
			break;
	}
}

void GameObject::Draw(Camera& camera)
{
	transform.SetPos(glm::vec3(0.0f, 0.0f, 5.0f));
	transform.SetRot(glm::vec3(0.0f, 0.0f, 0.0f));
	transform.SetScale(glm::vec3(1.0f, 1.0f, 1.0f));
	
	shader.Bind();
	shader.Update(transform, camera);
	linkShader(camera);

	texture.Bind(0);

	mesh.Draw();
}

void GameObject::linkShader(Camera& camera)
{
	switch (objShaderType)
	{
		case ShaderType::Default:
			break;
		case ShaderType::EnviromentMapping:
			glm::mat4 model = transform.GetModel();

			glm::mat4 view = camera.GetViewProjection();

			glm::mat4 modelView = view * model;
			shader.setVec3("camPos", camera.getPos());
			shader.setFloat("reflectiveness", .75f);

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			shader.setMat4("model", transform.GetModel());
			shader.setMat4("transform", modelView);
			GLuint diffuseTexLocation = glGetUniformLocation(shader.getId(), "diffuse");
			GLuint skyboxTexLocation = glGetUniformLocation(shader.getId(), "skybox");

			glUniform1i(diffuseTexLocation, 1);
			glUniform1i(skyboxTexLocation, 0);

			glActiveTexture(GL_TEXTURE0 + 1);
			glBindTexture(GL_TEXTURE_2D, texture.getID());
			break;
	}
}