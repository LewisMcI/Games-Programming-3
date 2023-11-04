#include "Shader.h"

Shader::Shader(){
	shaderID = 0;
	GLuint shaders[NUM_SHADERS]{};
	GLuint uniforms[NUM_UNIFORMS]{};
}
void Shader::initShader(const std::string& vertShader, const std::string& fragShader)
{
	// Create an empty program object
	shaderID = glCreateProgram();

	// Create vertex shader
	shaders[0] = CreateShader(LoadShader(vertShader), GL_VERTEX_SHADER);
	// Create Fragment Shader
	shaders[1] = CreateShader(LoadShader(fragShader), GL_FRAGMENT_SHADER);
	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glAttachShader(shaderID, shaders[i]);
	}
	// Associates attribute value to shader value
	glBindAttribLocation(shaderID, 0, "position");
	glBindAttribLocation(shaderID, 1, "texCoord");

	// Link program object - Used to create executable that is run on the programmable vertex/geometry/fragment processor depending on shader objects type
	glLinkProgram(shaderID);

	// Error Checks
	CheckShaderError(shaderID, GL_LINK_STATUS, true, "Error: Shader program linking has failed");
	glValidateProgram(shaderID);
	CheckShaderError(shaderID, GL_VALIDATE_STATUS, true, "Error: Shader program not valid");
	uniforms[TRANSFORM_U] = glGetUniformLocation(shaderID, "transform");
}

void Shader::initShader(const std::string& vertShader, const std::string& fragShader, const std::string& geometryShader)
{
	// Create an empty program object
	shaderID = glCreateProgram();

	// Create vertex shader
	shaders[0] = CreateShader(LoadShader(vertShader), GL_VERTEX_SHADER);
	// Create Fragment Shader
	shaders[1] = CreateShader(LoadShader(geometryShader), GL_GEOMETRY_SHADER);
	// Create Geometry Shader
	shaders[2] = CreateShader(LoadShader(fragShader), GL_FRAGMENT_SHADER);
	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glAttachShader(shaderID, shaders[i]);
	}
	// Associates attribute value to shader value
	glBindAttribLocation(shaderID, 0, "position");
	glBindAttribLocation(shaderID, 1, "texCoord");

	// Link program object - Used to create executable that is run on the programmable vertex/geometry/fragment processor depending on shader objects type
	glLinkProgram(shaderID);

	// Error Checks
	CheckShaderError(shaderID, GL_LINK_STATUS, true, "Error: Shader program linking has failed");
	glValidateProgram(shaderID);
	CheckShaderError(shaderID, GL_VALIDATE_STATUS, true, "Error: Shader program not valid");
	uniforms[TRANSFORM_U] = glGetUniformLocation(shaderID, "transform");
}

Shader::~Shader()
{
	// For each shader
	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		// Detach shader from program
		glDetachShader(shaderID, shaders[i]);
		// Delete Shader
		glDeleteShader(shaders[i]);
	}
	// Delete progam
	glDeleteProgram(shaderID);
}

void Shader::Bind()
{
	// Bind Program
	glUseProgram(shaderID);
}

void Shader::Update(const TransformComponent& transform, const Camera& camera)
{
	// Get view projection matrix and update shader.
	glm::mat4 mvp = camera.GetViewProjection() * transform.GetModel();
	glUniformMatrix4fv(uniforms[TRANSFORM_U], 1, GLU_FALSE, &mvp[0][0]);
}


GLuint Shader::CreateShader(const std::string& text, unsigned int type)
{
	// Create shader
	GLuint shader = glCreateShader(type); //create shader based on specified type

	// If shader failed to create
	if (shader == 0) 
	{
		std::cerr << "Shader Creation failed " << type << std::endl;
	}

	// Convert string
	const GLchar* stringSource[1];
	stringSource[0] = text.c_str();
	GLint lengths[1];
	lengths[0] = text.length();

	// Send Shader to OpenGL
	glShaderSource(shader, 1, stringSource, lengths); 
	// Compile Shader
	glCompileShader(shader);

	// Error check
	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error compiling shader."); 

	return shader;
}

std::string Shader::LoadShader(const std::string& fileName)
{
	// Open file
	std::ifstream file;
	file.open((fileName).c_str());

	std::string output;
	std::string line;

	// If file was opened
	if (file.is_open())
	{
		// Append each line
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	// File could not be opened
	else
	{
		std::cerr << "Could not load shader: " << fileName << std::endl;
	}

	return output;
}


void Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}