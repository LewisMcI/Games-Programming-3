#include "MainGame.h"
#include "Camera.h"
#include <iostream>
#include <string>


Transform transform;

MainGame::MainGame()
{
	_gameState = GameState::PLAY;
	Display* _gameDisplay = new Display(); //new display
	Shader fogShader();
	Shader toonShader();
	Shader rimShader();
	Shader geoShader();
	//Audio* audioDevice();
}

MainGame::~MainGame()
{
}

void MainGame::run()
{
	initSystems(); 
	gameLoop();
}

void MainGame::initSystems()
{
	followMesh = true;
	followingMesh1 = true;
	usingMouseMovement = true;
	_gameDisplay.initDisplay(); 
	//whistle = audioDevice.loadSound("..\\res\\bang.wav");
	//backGroundMusic = audioDevice.loadSound("..\\res\\background.wav");
	
	mesh1.loadModel("..\\res\\monkey3.obj");
	mesh2.loadModel("..\\res\\monkey3.obj");
	mesh3.loadModel("..\\res\\monkey3.obj");
	fogShader.init("..\\res\\fogShader.vert", "..\\res\\fogShader.frag"); //new shader
	toonShader.init("..\\res\\shaderToon.vert", "..\\res\\shaderToon.frag"); //new shader
	rimShader.init("..\\res\\shaderRim.vert", "..\\res\\shaderRim.frag");
	eMapping.init("..\\res\\shaderReflection.vert", "..\\res\\shaderReflection.frag");

	geoShader.initGeo();

	myCamera.initCamera(glm::vec3(0, 0, -5), 70.0f, (float)_gameDisplay.getWidth()/_gameDisplay.getHeight(), 0.01f, 1000.0f);

	counter = 1.0f;

	vector<std::string> faces
	{
		"..\\res\\skybox\\right.jpg",
		"..\\res\\skybox\\left.jpg",
		"..\\res\\skybox\\top.jpg",
		"..\\res\\skybox\\bottom.jpg",
		"..\\res\\skybox\\front.jpg",
		"..\\res\\skybox\\back.jpg"
	};

	skybox.init(faces);
}

void MainGame::gameLoop()
{
	while (_gameState != GameState::EXIT)
	{
		processInput();
		drawGame();
		collision(mesh1.getSpherePos(), mesh1.getSphereRadius(), mesh2.getSpherePos(), mesh2.getSphereRadius());
		//playAudio(backGroundMusic, glm::vec3(0.0f,0.0f,0.0f));
	}
}

void MainGame::processInput()
{
	SDL_Event evnt;

	while (SDL_PollEvent(&evnt)) //get and process events
	{
		switch (evnt.type)
		{
			// Quit Game
			case SDL_QUIT:
				_gameState = GameState::EXIT;
				break;
			case SDL_MOUSEMOTION:
				if (usingMouseMovement)
					break;
				// Upward/Downward
				myCamera.MoveUpward(evnt.motion.xrel * 0.001f);
				// Left/Right
				myCamera.MoveRight(evnt.motion.yrel * 0.001f);
				break;
			case SDL_KEYDOWN:
				switch (evnt.key.keysym.sym) {
					// Upward
					case SDLK_w:
						if (!usingMouseMovement)
							break;
						cout << "\nForward Key Clicked";
						myCamera.MoveUpward(.02);
						break;
						// Downward
					case SDLK_s:
						if (!usingMouseMovement)
							break;
						cout << "\nBackward Key Clicked";
						myCamera.MoveUpward(-.02);
						break;
						// Right
					case SDLK_d:
						if (!usingMouseMovement)
							break;
						cout << "\nRight Key Clicked";
						myCamera.MoveRight(.02);
						break;
						// Left
					case SDLK_a:
						if (!usingMouseMovement)
							break;
						cout << "\nLeft Key Clicked";
						myCamera.MoveRight(-.02);
						break;
					
					case SDLK_z:
						cout << "\Z Key Clicked";
						followingMesh1 = !followingMesh1;
						break;

					case SDLK_x:
						cout << "\X Key Clicked";
						usingMouseMovement = !usingMouseMovement;
						break;

					case SDLK_c:
						cout << "\C Key Clicked";
						followMesh = !followMesh;
						break;
				}
				break;
			// Mouse Button
			case SDL_MOUSEBUTTONDOWN:
				switch (evnt.button.button)
				{
					// Left Mouse Click
					case SDL_BUTTON_LEFT:
						cout << "\nLeft Mouse Click";
						break;
					// Right Mouse Click
					case SDL_BUTTON_RIGHT:
						cout << "\nRight Mouse Click";
						break;
				}
				break;
			// Mouse Wheel
			case SDL_MOUSEWHEEL:
				// Up Scroll
				if (evnt.wheel.y > 0)
				{
					cout << "\nScroll Upward";
					myCamera.MoveForward(.04);
				}
				// Down Scroll
				else if (evnt.wheel.y < 0)
				{
					cout << "\nScroll Downward";
					myCamera.MoveForward(-.04);
				}
				break;
			
		}
	}
	
}


bool MainGame::collision(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad)
{
	float distance = glm::sqrt((m2Pos.x - m1Pos.x)*(m2Pos.x - m1Pos.x) + (m2Pos.y - m1Pos.y)*(m2Pos.y - m1Pos.y) + (m2Pos.z - m1Pos.z)*(m2Pos.z - m1Pos.z));

	if (distance < (m1Rad + m2Rad))
	{
		//audioDevice.setlistener(myCamera.getPos(), m1Pos); //add bool to mesh
		//playAudio(whistle, m1Pos);
		return true;
	}
	else
	{
		return false;
	}
}

//void MainGame::playAudio(unsigned int Source, glm::vec3 pos)
//{
//	
//	ALint state; 
//	alGetSourcei(Source, AL_SOURCE_STATE, &state);
//	/*
//	Possible values of state
//	AL_INITIAL
//	AL_STOPPED
//	AL_PLAYING
//	AL_PAUSED
//	*/
//	if (AL_PLAYING != state)
//	{
//		audioDevice.playSound(Source, pos);
//	}
//}

void MainGame::linkFogShader()
{
	//fogShader.setMat4("u_pm", myCamera.getProjection());
	//fogShader.setMat4("u_vm", myCamera.getProjection());
	fogShader.setFloat("maxDist", 20.0f);
	fogShader.setFloat("minDist", 0.0f);
	fogShader.setVec3("fogColor", glm::vec3(0.0f, 0.0f, 0.0f));
}

void MainGame::linkToon()
{
	toonShader.setVec3("lightDir", glm::vec3(0.5f, 0.5f, 0.5f));
}

void MainGame::linkGeo()
{
	float randX = ((float)rand() / (RAND_MAX));
	float randY = ((float)rand() / (RAND_MAX));
	float randZ = ((float)rand() / (RAND_MAX));
	// Frag: uniform float randColourX; uniform float randColourY; uniform float randColourZ;
	geoShader.setFloat("randColourX", randX);
	geoShader.setFloat("randColourY", randY);
	geoShader.setFloat("randColourZ", randZ);
	// Geom: uniform float time;
	geoShader.setFloat("time", counter);
}

void MainGame::linkRimLighting()
{
	glm::vec3 camDir;
	camDir = mesh2.getSpherePos() - myCamera.getPos();
	camDir = glm::normalize(camDir);
	rimShader.setMat4("u_pm", myCamera.getProjection());
	rimShader.setMat4("u_vm", myCamera.getView());
	rimShader.setMat4("model", transform.GetModel());
	rimShader.setMat4("view", myCamera.getView());
	rimShader.setVec3("lightDir", glm::vec3(0.5f, 0.5f, 0.5f));
}

void MainGame::linkEmapping()
{
	eMapping.setMat4("projection", myCamera.getProjection());
	eMapping.setMat4("view", myCamera.getView());
	eMapping.setMat4("model", transform.GetModel());
	eMapping.setVec3("cameraPos", myCamera.getPos());
}

void MainGame::drawGame()
{
	_gameDisplay.clearDisplay(0.8f, 0.8f, 0.8f, 1.0f); //sets our background colour
	
	//linkFogShader();
	//linkToon();
	//linkRimLighting();

	Texture texture("..\\res\\bricks.jpg"); //load texture
	Texture texture1("..\\res\\water.jpg"); //load texture
	//texture1.Bind(0);

	transform.SetPos(glm::vec3(0.0, -sinf(counter), 0.0));
	transform.SetRot(glm::vec3(0.0, counter * 5, 0.0));
	transform.SetScale(glm::vec3(0.6, 0.6, 0.6));

	toonShader.Bind();
	linkToon();
	toonShader.Update(transform, myCamera);
	mesh1.draw();
	mesh1.updateSphereData(*transform.GetPos(), 0.62f);

	transform.SetPos(glm::vec3(0.0, -sinf(counter), -10.0));
	transform.SetRot(glm::vec3(0.0, counter * 5, 0.0));
	transform.SetScale(glm::vec3(0.6, 0.6, 0.6));

	toonShader.Bind();
	linkToon();
	toonShader.Update(transform, myCamera);
	mesh3.draw();
	mesh3.updateSphereData(*transform.GetPos(), 0.62f);

	linkEmapping();
	eMapping.Bind();	

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skybox.textureID);
	mesh2.draw();
	mesh2.updateSphereData(*transform.GetPos(), 0.62f);

	counter = counter + 0.02f;

	skybox.draw(&myCamera);	
	

	glEnableClientState(GL_COLOR_ARRAY); 
	glEnd();


	_gameDisplay.swapBuffer();	
	if (followMesh) {
		if (followingMesh1)
			myCamera.LookAt(mesh1.getSpherePos());
		else
			myCamera.LookAt(mesh3.getSpherePos());
	}
} 