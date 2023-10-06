#include "Display.h"

Display::Display()
{
	// We will initialize the window as null	
	sdlWindow = nullptr;
	screenWidth = 1089.1f;
	screenHeight = 800.1f;
}

Display::~Display()
{
	// Delete the context
	SDL_GL_DeleteContext(glContext);
	// Delete the window
	SDL_DestroyWindow(sdlWindow);
	// Quit SDL
	SDL_Quit();
}

float Display::getHeight() {
	return screenHeight;
}
float Display::getWidth() {
	return screenWidth;
}

void Display::clearDisplay(float r, float g, float b, float a)
{
	// Clears screen and sets background color to RGBA given.
	glClearColor(r, g, b, a);
	// Clear colour and depth buffer - Set colour to colour defined in glClearColour
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Display::returnError(std::string errorString)
{
	// Output string.
	cout << errorString;
	// Get user input
	char x;
	cin >> x;
	SDL_Quit();
}
void Display::swapBuffer()
{
	SDL_GL_SwapWindow(sdlWindow);
}
void Display::initDisplay()
{
	// Initialize SDL.
	SDL_Init(SDL_INIT_EVERYTHING);
	// Enable Double Buffer.
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	// Create window with args.
	sdlWindow = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, (int)screenWidth, (int)screenHeight, SDL_WINDOW_OPENGL);
	// Calls the returnError method if the Window failed to initialize.
	if (sdlWindow == nullptr) {
		returnError("Window failed to initialize");
	}

	// Creates context using window;
	SDL_GLContext glContext = SDL_GL_CreateContext(sdlWindow);

	// Calls the returnError method if the Context failed to initialize.
	if (glContext == nullptr)
	{
		returnError("GLContext failed to initialize");
	}

	// Initializes GLEW.
	GLenum error = glewInit();
	// Calls the returnError method if GLEW faield to initialize.
	if (error != GLEW_OK)
	{
		returnError("Glew failed to initialize");
	}

	// Enable Z-Buffering
	glEnable(GL_DEPTH_TEST);
	// Enable Cull
	glEnable(GL_CULL_FACE); 
	// Sets background colour of window.
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	// Hide Cursor and keep within SDL window
	SDL_SetRelativeMouseMode(SDL_TRUE);
}