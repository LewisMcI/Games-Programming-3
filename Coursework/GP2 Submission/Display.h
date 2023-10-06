#pragma once
#include <SDL/SDL.h>
#include <GL\glew.h>
#include <iostream>
#include <string>
using namespace std;


class Display
{
public:
	Display();
	~Display();
	void initDisplay();
	void swapBuffer();
	void clearDisplay(float r, float g, float b, float a);

	float getWidth();
	float getHeight();

private:

	void returnError(std::string errorString);
	// Global Variable to hold context
	SDL_GLContext glContext;
	// Holds pointer to window
	SDL_Window* sdlWindow;
	float screenWidth;
	float screenHeight;
};

