#include "Display.h"


Display::Display()
{
	// We will initialize the window as null	
	sdlWindow = nullptr;
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
	return DISPLAY_HEIGHT;
}
void Display::initFBO()
{
	glGenFramebuffers(1, &FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);

	// create a colorbuffer for attachment texture
	glGenTextures(1, &CBO);
	glBindTexture(GL_TEXTURE_2D, CBO); 
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, DISPLAY_WIDTH, DISPLAY_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, CBO, 0);

	// create a renderbuffer object for depth and stencil attachment 
	glGenRenderbuffers(1, &RBO);
	glBindRenderbuffer(GL_RENDERBUFFER, RBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, DISPLAY_WIDTH, DISPLAY_HEIGHT); // use a single renderbuffer object for both a depth AND stencil buffer.
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO); // now actually attach it

	// now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE && USE_INFO_DEBUGGING)
		std::cout << "FRAMEBUFFER:: Framebuffer is complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//FBOShader.initShader("..\\Resources\\Shaders\\FBO\\FBOShader.vert", "..\\Resources\\Shaders\\FBO\\FBOShader.frag");
	FBOShader.initShader("..\\Resources\\Shaders\\Kuwahara.vert", "..\\Resources\\Shaders\\Kuwahara.frag");
}

void Display::bindFBO()
{
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Display::unbindFBO()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Display::renderFBO()
{
	float quadVertices[] = {
		//positions   // texCoords
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f
	};
	// cube VAO
	glGenVertexArrays(1, &quadVAO);
	glGenBuffers(1, &quadVBO);
	glBindVertexArray(quadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	glDisable(GL_DEPTH_TEST);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // set clear color to white (not really necessary actually, since we won't be able to see behind the quad anyways)
	glClear(GL_COLOR_BUFFER_BIT);

	FBOShader.Bind();
	counter += .7f;
	//FBOShader.setFloat("random", counter);
	glBindVertexArray(quadVAO);
	glBindTexture(GL_TEXTURE_2D, CBO);	// use the color attachment texture as the texture of the quad plane
	glDrawArrays(GL_TRIANGLES, 0, 6);
}
float Display::getWidth() {
	return DISPLAY_WIDTH;
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
	//SDL_Init(SDL_INIT_EVERYTHING);
	// Enable Double Buffer.
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	// Create window with args.
	sdlWindow = SDL_CreateWindow("Asteroids (or something)", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, (int)DISPLAY_WIDTH, (int)DISPLAY_HEIGHT, SDL_WINDOW_OPENGL);
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
	//SDL_SetRelativeMouseMode(SDL_TRUE);
	initFBO();
}