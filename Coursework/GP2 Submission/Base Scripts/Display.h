#pragma once
#define SDL_MAIN_HANDLED 
#include <SDL2/SDL.h>
#include <GL\glew.h>
#include <string>
#include "../Other/GlobalVariables.h"
#include "Shader.h"

class Display
{
public:
	Display();

	~Display()
	{
		// Cleanup and destroy the FBO and related resources
		glDeleteFramebuffers(1, &FBO);
		glDeleteRenderbuffers(1, &RBO);
		glDeleteTextures(1, &CBO);

		// Cleanup and destroy the quad VAO and VBO
		glDeleteVertexArrays(1, &quadVAO);
		glDeleteBuffers(1, &quadVBO);

		// Destroy the SDL window and OpenGL context
		SDL_GL_DeleteContext(glContext);
		SDL_DestroyWindow(sdlWindow);

		// Quit SDL
		SDL_Quit();
	}
	void initDisplay();
	void swapBuffer();
	void clearDisplay(float r, float g, float b, float a);

	void initFBO();
	void bindFBO();
	void unbindFBO();
	void renderFBO();

private:
	void returnError(std::string errorString);
	// Global Variable to hold context
	SDL_GLContext glContext;
	// Holds pointer to window
	SDL_Window* sdlWindow;

	GLuint FBO;
	GLuint RBO;
	GLuint CBO;
	GLuint quadVAO;
	GLuint quadVBO;
	Shader FBOShader;

	float counter = 0;
};

