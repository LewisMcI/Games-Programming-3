#pragma once
#include <string>
#include <GL\glew.h>

class Texture
{
public:
	Texture();
	void initTexture(const std::string& imgPath);
	void initCubemap(const std::string& rightImgPath, const std::string& leftImgPath, const std::string& topImgPath, const std::string& bottomImgPath, const std::string& frontImgPath, const std::string& backImgPath);
	void loadNormals(const std::string& fileName);
	void Bind(unsigned int unit); // bind upto 32 textures
	/*void initTexture(const std::string& fileName);*/

	GLuint getID() { return textureHandler; }
	~Texture();
	

protected:
private:

	GLuint textureHandler;
};

