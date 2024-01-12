#pragma once
#include <string>
#include <map>
#include <GL\glew.h>
#include <unordered_map>

enum class TextureType { Default, Brick, Metal, Laser, Asteroid, Player };
class TextureLoader
{
public:
	TextureLoader() = default;

	static TextureLoader& getInstance() {
		static TextureLoader instance;
		return instance;
	}

	GLuint initTexture(TextureType& textureType);

	GLuint getID(TextureType textureType) { 
		const std::string& imgPath = texturePaths[textureType];

		GLuint textureId;
		return textureIds[imgPath]; }
	~TextureLoader();

	void Bind(TextureType& textureTypeToBind, unsigned int unit);

	

protected:
private:
	std::unordered_map<std::string, GLuint> textureIds;

	std::map<TextureType, std::string> texturePaths = {
		{ TextureType::Default, "..\\Resources\\Textures\\DefaultTexture.jpg" },
		{ TextureType::Brick, "..\\Resources\\Textures\\Bricks\\BrickAlbedo.png" },
		{ TextureType::Metal, "..\\Resources\\Textures\\metal.jpg"},
		{ TextureType::Laser, "..\\Resources\\Textures\\laser.png"},
		{ TextureType::Asteroid, "..\\Resources\\Textures\\asteroid.jpg"},
		{ TextureType::Player, "..\\Resources\\Textures\\player.png"}

	};
};

