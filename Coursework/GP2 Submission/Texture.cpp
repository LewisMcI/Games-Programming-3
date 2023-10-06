#include "Texture.h"
#include "stb_image.h"
#include <cassert>
#include <iostream>
Texture::Texture() {
	textureHandler = 0;
}
void Texture::initTexture(const std::string& imgPath)
{
	int width, height, numOfComponents;
	// Load Image
	unsigned char* data = stbi_load((imgPath).c_str(), &width, &height, &numOfComponents, 4);
	// If data could not be loaded
	if (data == NULL)
	{
		std::cerr << "Failed to load texture" << imgPath << std::endl;
	}

	// Generates texture names
	glGenTextures(1, &textureHandler);

	// Bind the newly created textureHandler
	glBindTexture(GL_TEXTURE_2D, textureHandler);
	// Specify the 2D texture image (Target, Mipmapping Level, Internal Format, Width, Height, Border Size, Format, Type, Image Data)
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	// Enable Linear Filtering for minification and magnification
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Wrap Textures with Width and Height
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);



	glBindTexture(textureHandler, 0);
	// Free memory allocated by STBI_LOAD
	stbi_image_free(data);
}
void Texture::initCubemap(const std::string& rightImgPath, const std::string& leftImgPath, const std::string& topImgPath,
	const std::string& bottomImgPath, const std::string& frontImgPath, const std::string& backImgPath )
{
	std::string faces[6] =
	{
		rightImgPath,
		leftImgPath,
		topImgPath,
		bottomImgPath,
		frontImgPath,
		backImgPath
	};
	int width, height, numOfComponents;


	// Generates texture names
	glGenTextures(1, &textureHandler);

	// Bind the newly created textureHandler
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureHandler);

	// Enable Linear Filtering for minification and magnification
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Wrap Textures with Width and Height
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT);

	for (GLuint i = 0; i < 6; i++)
	{
		// Load Image
		unsigned char* data = stbi_load((faces[i]).c_str(), &width, &height, &numOfComponents, 4);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0,
			GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
		);

		stbi_image_free(data);
		// If data could not be loaded
		if (data == NULL)
		{
			std::cerr << "Failed to load texture" << faces[i] << std::endl;
		}

	}


	glBindTexture(textureHandler, 0);
	// Free memory allocated by STBI_LOAD
}
void Texture::loadNormals(const std::string& fileName)
{
	textureHandler = 1;
	int width, height, numComponents; //width, height, and no of components of image
	unsigned char* imageData = stbi_load((fileName).c_str(), &width, &height, &numComponents, 4); //load the image and store the data

	if (imageData == NULL)
	{
		std::cerr << "texture load failed" << fileName << std::endl;
	}

	glGenTextures(1, &textureHandler); // number of and address of textures
	glBindTexture(GL_TEXTURE_2D, textureHandler); //bind texture - define type 

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // wrap texture outside width
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // wrap texture outside height

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // linear filtering for minification (texture is smaller than area)
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // linear filtering for magnifcation (texture is larger)

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData); //Target, Mipmapping Level, Pixel Format, Width, Height, Border Size, Input Format, Data Type of Texture, Image Data

	stbi_image_free(imageData);
}

Texture::~Texture()
{
	// Deletes Textures
	glDeleteTextures(1, &textureHandler);
}

void Texture::Bind(unsigned int unit)
{
	// Ensures the maximum number of active textures is not greater than the maximum number of simultaneous multitextures
	assert(unit >= 0 && unit <= GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS);
	// Set Active Texture unit
	glActiveTexture(GL_TEXTURE0 + unit); 
	// Bind Texture
	glBindTexture(GL_TEXTURE_2D, textureHandler); //type of and texture to bind to unit
}
