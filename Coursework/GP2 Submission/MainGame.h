#pragma once

#include <SDL\SDL.h>
#include <GL/glew.h>
#include "Display.h" 
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "transform.h"
#include "Audio.h"
#include "Time.h"
#include "SkyBox.h"
#include <list>
#include "GameObject.h"


enum class GameState{PLAY, EXIT};

class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();

private:

	void initSystems();
	void processInput();
	void gameLoop();
	void drawGame();
	void drawObjects();
	bool handleCollision(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad);
	void linkToonShader();
	void linkRimShader();
	void linkToonAndRimShader();
	void linkToffeeShader();
	void linkSpecularShader(glm::vec3 colour);
	void linkToonSpecularShader(glm::vec3 colour);
	void linktRimExplodeShader();
	void linkChromaticAbberation();
	void linkBumpShader();

	void linkGeoShader();
	void linkEnvironmentMapping(float Reflectiveness);
	void linkBoxBlurShader(int blurFactor);
	void linkGaussianBlurShader(int blurFactor = 2);
	void linkKuhawaraShader(int blurFactor);

	void checkCollisions();
	void drawExplodeObj();
	void drawEnvironmentMappingObjs();
	void drawNormalPlane();
	void drawBoxBlurFilterPlane();
	void drawGaussianBlurFilterPlane();
	void drawKuwaharaFilterPlane();
	void drawTRimExplodeObj();
	void drawChromaticAbberationPlane();

	void processKeyboardInput(SDL_Keysym keySym);
	void processMouseInput(SDL_MouseMotionEvent event);

	void createGameObject();
	void drawGameObjects();

	Display display;
	GameState gameState;

	Mesh mesh1;
	Mesh mesh2;
	Mesh mesh3;
	Mesh mesh4;
	Mesh mesh5;
	Mesh quad;
	Texture texture1;
	Texture texture2;
	Texture texture3;
	Texture texture4;
	Texture bumpTexture;

	Shader environmentMapping;
	Shader shader;
	Shader fogShader;
	Shader toonShader;
	Shader rimShader;
	Shader toonAndRimShader;
	Shader toffeeShader;
	Shader specularShader;
	Shader toonSpecularShader;
	Shader bumpShader;
	Shader geoShader;
	Shader tRimExplodeShader;
	Shader chromaticAbberationShader;

	Shader shaderSkybox;

	Skybox skybox;

	Shader boxBlurShader;
	Shader gaussianShader;
	Shader kuwaharaShader;

	Camera myCamera;

	Transform transform;

	Audio audioSource;

	Time time;

	std::vector<GameObject> gameObjects;

	bool colliding1 = false;
	bool colliding2 = false;

	int invertCounter = 1.0f;
	float movementSpeed = 1.0f;
	float rotationSpeed = 5.0f;
	float randX;
	float randY;
	float randZ;
};

