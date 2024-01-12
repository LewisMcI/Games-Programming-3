#pragma once
#include <vector>
#include <GL\glew.h>
#include "stb_image.h"
#include "Shader.h"
#include <iostream>
#include "Camera.h"

class Skybox
{
public:
	Skybox() {
		init();
	}
	void draw(Camera* camera);

	unsigned int textureID;
	unsigned int skyboxVAO;
	unsigned int skyboxVBO;

private:
	void init();

	Shader shader;

};

