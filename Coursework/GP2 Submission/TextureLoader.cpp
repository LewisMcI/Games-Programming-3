#include "TextureLoader.h"
#include "stb_image.h"
#include <cassert>
#include <iostream>

GLuint TextureLoader::initTexture(TextureType& textureType)
{
	const std::string& imgPath = texturePaths[textureType];
	// Check if the texture has already been loaded
	if (textureIds.find(imgPath) != textureIds.end()) {
		return textureIds[imgPath]; // Return the cached texture ID
	}


	int width, height, numOfComponents;
	// Load Image
	unsigned char* data = stbi_load((imgPath).c_str(), &width, &height, &numOfComponents, 4);
	// If data could not be loaded
	if (data == NULL)
	{
		std::cerr << "Failed to load texture" << imgPath << std::endl;
	}

	GLuint textureId;

	// Generates texture names
	glGenTextures(1, &textureId);

	// Bind the newly created textureHandler
	glBindTexture(GL_TEXTURE_2D, textureId);

	// Specify the 2D texture image (Target, Mipmapping Level, Internal Format, Width, Height, Border Size, Format, Type, Image Data)
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	// Enable Linear Filtering for minification and magnification
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Wrap Textures with Width and Height
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindTexture(GL_TEXTURE_2D, 0);
	// Free memory allocated by STBI_LOAD
	stbi_image_free(data);

	// Cache the texture for future use
	textureIds[imgPath] = textureId;
}

TextureLoader::~TextureLoader()
{
	// Deletes Textures
	for (auto& pair : textureIds) {
		glDeleteTextures(1, &pair.second);
	}
}

void TextureLoader::Bind(TextureType& textureTypeToBind, unsigned int unit)
{
	const std::string& imgPath = texturePaths[textureTypeToBind];

	GLuint textureId;
	// Cache the texture for future use
	textureId = textureIds[imgPath];

	// Ensures the maximum number of active textures is not greater than the maximum number of simultaneous multitextures
	assert(unit >= 0 && unit <= GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS);	
	// Set Active Texture unit
	glActiveTexture(GL_TEXTURE0 + unit); 
	// Bind Texture
	glBindTexture(GL_TEXTURE_2D, textureId); //type of and texture to bind to unit
}
