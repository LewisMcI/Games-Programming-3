#include "MainGame.h"
#include "Camera.h"
#include <iostream>
#include <string>

// Constructor
MainGame::MainGame()
{
	gameState = GameState::PLAY;
	// Sets up the game state.
	Display* display;
}

// Destructor
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
	// Initialize Display
	display.initDisplay();


	randX = (float)rand() / RAND_MAX;
	randY = (float)rand() / RAND_MAX;
	randZ = (float)rand() / RAND_MAX;
	// Load Models
	mesh1.loadModel("..\\Resources\\Models\\Cube.obj");
	mesh2.loadModel("..\\Resources\\Models\\dog.obj");
	mesh3.loadModel("..\\Resources\\Models\\Destructor Pesado Finalizer.obj");
	mesh4.loadModel("..\\Resources\\Models\\draven.obj");
	mesh5.loadModel("..\\Resources\\Models\\Sphere.obj");

	Vertex vertices[] = { Vertex(glm::vec3(-1.0, 1.0, 0), glm::vec2(0.0, 1.0)),
						Vertex(glm::vec3(1.0, 1.0, 0), glm::vec2(1.0, 1.0)),
						Vertex(glm::vec3(-1.0, -1.0, 0), glm::vec2(0.0, 0.0)),
						Vertex(glm::vec3(-1.0, -1.0, 0), glm::vec2(0.0, 0.0)),
						Vertex(glm::vec3(1.0, 1.0, 0), glm::vec2(1.0, 1.0)),
						Vertex(glm::vec3(1.0, -1.0, 0), glm::vec2(1.0, 0.0)) };
	quad.loadVertexs(vertices, sizeof(vertices) / sizeof(vertices[0]));

	// Load Shaders
	shader.initShader("..\\Resources\\Shaders\\DefaultShader.vert", "..\\Resources\\Shaders\\DefaultShader.frag");
	fogShader.initShader("..\\Resources\\Shaders\\FogVertexShader.vert", "..\\Resources\\Shaders\\FogFragmentShader.frag");
	toonShader.initShader("..\\Resources\\Shaders\\ToonVertexShader.vert", "..\\Resources\\Shaders\\ToonFragmentShader.frag");
	rimShader.initShader("..\\Resources\\Shaders\\RimLightingVertex.vert", "..\\Resources\\Shaders\\RimLightingFragment.frag");
	toonAndRimShader.initShader("..\\Resources\\Shaders\\TRimLightingVertex.vert", "..\\Resources\\Shaders\\TRimLightingFragment.frag");
	toffeeShader.initShader("..\\Resources\\Shaders\\ToffeeVertex.vert", "..\\Resources\\Shaders\\ToffeeFragment.frag");
	specularShader.initShader("..\\Resources\\Shaders\\SpecularLighting.vert", "..\\Resources\\Shaders\\SpecularLighting.frag");
	toonSpecularShader.initShader("..\\Resources\\Shaders\\ToonSpecularLighting.vert", "..\\Resources\\Shaders\\ToonSpecularLighting.frag");
	geoShader.initShader("..\\Resources\\Shaders\\shaderGeoText.vert", "..\\Resources\\Shaders\\shaderGeoText.frag", "..\\Resources\\Shaders\\shaderGeoText.geom");
	tRimExplodeShader.initShader("..\\Resources\\Shaders\\RimAndToonAndExplodeShaders\\TRimLightingExplode.vert", "..\\Resources\\Shaders\\RimAndToonAndExplodeShaders\\TRimLightingExplode.frag", "..\\Resources\\Shaders\\RimAndToonAndExplodeShaders\\TRimLightingExplode.geom");

	boxBlurShader.initShader("..\\Resources\\Shaders\\BoxBlur.vert", "..\\Resources\\Shaders\\BoxBlur.frag");
	gaussianShader.initShader("..\\Resources\\Shaders\\GaussianBlur.vert", "..\\Resources\\Shaders\\GaussianBlur.frag");
	kuwaharaShader.initShader("..\\Resources\\Shaders\\Kuwahara.vert", "..\\Resources\\Shaders\\Kuwahara.frag");
	chromaticAbberationShader.initShader("..\\Resources\\Shaders\\ChromaticAbberation.vert", "..\\Resources\\Shaders\\ChromaticAbberation.frag");
	environmentMapping.initShader("..\\Resources\\Shaders\\EnvironmentMapping.vert", "..\\Resources\\Shaders\\EnvironmentMapping.frag");
	// Load Textures
	texture1.initTexture("..\\Resources\\Textures\\Bricks\\BrickAlbedo.png");
	texture2.initTexture("..\\Resources\\Textures\\DogTexture.png");
	texture3.initTexture("..\\Resources\\Textures\\Destructor.jpeg");
	texture4.initTexture("..\\Resources\\Textures\\testTexture1.jpg");
	bumpTexture.loadNormals("..\\Resources\\Textures\\NormalMap.jpg");

	vector<std::string> faces
	{
		"..\\Resources\\Textures\\Skybox\\right.png",
		"..\\Resources\\Textures\\Skybox\\left.png",
		"..\\Resources\\Textures\\Skybox\\top.png",
		"..\\Resources\\Textures\\Skybox\\bottom.png",
		"..\\Resources\\Textures\\Skybox\\front.png",
		"..\\Resources\\Textures\\Skybox\\back.png"
	};
	skybox.init(faces);
	// Initialize Camera
	myCamera.initCamera(glm::vec3(0, 0, -5), 70.0f, (float)display.getWidth() / display.getHeight(), 0.01f, 1000.0f);

	// Load and Play Audio
	//audioSource.addSFX("..\\Resources\\Audio\\retroSFX.wav");
	//audioSource.addTrack("..\\Resources\\Audio\\Background.wav");
	//audioSource.playTrack();
	createGameObject();
}

void MainGame::linkGeoShader()
{
	geoShader.setFloat("randColourX", randX);
	geoShader.setFloat("randColourY", randY);
	geoShader.setFloat("randColourZ", randZ);
	geoShader.setFloat("time", (float)time.getCurrentTime() + 2.5f);
}
void MainGame::linktRimExplodeShader()
{
	tRimExplodeShader.setMat4("modelMatrix", transform.GetModel());
	tRimExplodeShader.setVec3("lightDir", glm::vec3(0.5f, 0.5f, 0.5f));
	tRimExplodeShader.setFloat("rimPower", 5.0f);
	tRimExplodeShader.setVec3("rimColor", glm::vec3(1.0f, 0.0f, 0.0f));
	tRimExplodeShader.setVec3("camPos", myCamera.getPos());

	tRimExplodeShader.setFloat("time", (float)time.getCurrentTime());
}
void MainGame::linkChromaticAbberation() 
{
	chromaticAbberationShader.setMat4("transform", transform.GetModel());
	chromaticAbberationShader.setFloat("RED_OFFSET", sinf(time.getCurrentTime()));
	chromaticAbberationShader.setFloat("BLUE_OFFSET", sinf(time.getCurrentTime()));
	chromaticAbberationShader.setFloat("GREEN_OFFSET", sinf(time.getCurrentTime()));
}

void MainGame::linkEnvironmentMapping(float reflectiveness) {
	//// Define the model matrix (transforms from model space to world space)
	glm::mat4 model = transform.GetModel(); // Identity matrix

	//// Define the view matrix (transforms from world space to camera space)
	glm::mat4 view = myCamera.GetViewProjection();

	//// Calculate the model-view matrix
	glm::mat4 modelView = view * model;
	environmentMapping.setVec3("camPos", myCamera.getPos());
	environmentMapping.setFloat("reflectiveness", reflectiveness);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	environmentMapping.setMat4("model", transform.GetModel());
	environmentMapping.setMat4("transform", modelView);
	GLuint diffuseTexLocation = glGetUniformLocation(environmentMapping.getId(), "diffuse");
	GLuint skyboxTexLocation = glGetUniformLocation(environmentMapping.getId(), "skybox");

	glUniform1i(diffuseTexLocation, 1);
	glUniform1i(skyboxTexLocation, 0);

	glActiveTexture(GL_TEXTURE0 + 1);
	glBindTexture(GL_TEXTURE_2D, texture1.getID());

}
void MainGame::linkBoxBlurShader(int blurFactor)
{
	boxBlurShader.setMat4("transform", transform.GetModel());
	boxBlurShader.setInt("blurFactor", blurFactor);
}
void MainGame::linkGaussianBlurShader(int blurFactor)
{
	gaussianShader.setMat4("transform", transform.GetModel());
	gaussianShader.setInt("blurFactor", blurFactor);
}
void MainGame::linkKuhawaraShader(int blurFactor) 
{
	kuwaharaShader.setInt("blurFactor", blurFactor);
}


void MainGame::gameLoop()
{
	// While game is still playing. Processes inputs and draws the game.
	while (gameState != GameState::EXIT) 
	{
		processInput();
		drawGame(); 
		//checkCollisions();
	}
}
void MainGame::processKeyboardInput(SDL_Keysym keySym) {

	float distance = 2.0f;
	// Modifiers
	switch (keySym.mod) {
		// Move Faster Key
	case KMOD_LSHIFT:
		distance *= 2.0f;
		break;
		// Move Slower Key
	case KMOD_LCTRL:
		distance *= 0.25f;
		break;
	}
	// Movement Keys
	switch (keySym.sym) {
		// Forward Key
	case SDLK_UP:
	case SDLK_w:
		myCamera.MoveX(distance);
		break;
		// Backward Key
	case SDLK_DOWN:
	case SDLK_s:
		myCamera.MoveX(-distance);
		break;
		// Left Key
	case SDLK_LEFT:
	case SDLK_a:
		myCamera.MoveZ(distance);
		break;
		// Right Key
	case SDLK_RIGHT:
	case SDLK_d:
		myCamera.MoveZ(-distance);
		break;
		// Up Key
	case SDLK_SPACE:
		myCamera.MoveY(distance);
		break;
	}
}

void MainGame::processMouseInput(SDL_MouseMotionEvent event) {
	// Rotates X by the relative X value given through the cursor. (Must be inverted)
	myCamera.RotateX(-event.xrel * 0.001f);
	// Rotates Y by the relative Y value given through the cursor.
	myCamera.RotateY(event.yrel * 0.001f);
}

void MainGame::processInput()
{
	// Creates new Event.
	SDL_Event event;
	// While events are still coming in.
	while (SDL_PollEvent(&event)) 
	{
		// Switch statement
		switch (event.type)
		{
			// Quit
			case SDL_QUIT:
				gameState = GameState::EXIT;
				break;
			// OnKeyDown - Handles keyboard input to control camera.
			case SDL_KEYDOWN:
				this->processKeyboardInput(event.key.keysym);
				break;
			// OnMouseMove - Handles mouse movement to control camera.
			case SDL_MOUSEMOTION:
				this->processMouseInput(event.motion);
				break;
			default:
				break;
		}
	}
}

void MainGame::drawExplodeObj()
{
	transform.SetPos(glm::vec3(0.0f, 0.0f, 5.0f));
	transform.SetRot(glm::vec3(0.0f, time.getCurrentTime() * rotationSpeed * 0.01f, 0.0f));
	transform.SetScale(glm::vec3(1.0f, 1.0f, 1.0f));
	texture1.Bind(0);
	geoShader.Bind();
	geoShader.Update(transform, myCamera);
	linkGeoShader();

	mesh5.Draw();
}

void MainGame::drawEnvironmentMappingObjs()
{
	// Obj 1 (Fully Reflective)
	transform.SetPos(glm::vec3(-3.0f, -3.0f, 5.0f));
	transform.SetRot(glm::vec3(0.0f, time.getCurrentTime() * rotationSpeed * 0.01f, 0.0f));
	transform.SetScale(glm::vec3(1.0f, 1.0f, 1.0f));

	environmentMapping.Bind();
	environmentMapping.Update(transform, myCamera);
	linkEnvironmentMapping(1.0f);
	mesh1.Draw();


	// Obj 2 (Half Reflective)
	transform.SetPos(glm::vec3(0.0f, -3.0f, 5.0f));
	transform.SetRot(glm::vec3(0.0f, time.getCurrentTime() * rotationSpeed * 0.01f, 0.0f));
	transform.SetScale(glm::vec3(1.0f, 1.0f, 1.0f));

	environmentMapping.Bind();
	environmentMapping.Update(transform, myCamera);
	linkEnvironmentMapping(.5f);
	mesh1.Draw();


	// Obj 3 (Not Reflective)
	transform.SetPos(glm::vec3(3.0f, -3.0f, 5.0f));
	transform.SetRot(glm::vec3(0.0f, time.getCurrentTime() * rotationSpeed * 0.01f, 0.0f));
	transform.SetScale(glm::vec3(1.0f, 1.0f, 1.0f));

	environmentMapping.Bind();
	environmentMapping.Update(transform, myCamera);
	linkEnvironmentMapping(0.0f);
	mesh1.Draw();
}

void MainGame::drawNormalPlane()
{
	transform.SetPos(glm::vec3(1.5f, 0.0f, 15.0f));
	transform.SetRot(glm::vec3(0.0f, 0.0f, 0.0f));
	transform.SetScale(glm::vec3(1.0f, 1.0f, 1.0f));

	shader.Bind();
	shader.Update(transform, myCamera);
	texture4.Bind(0);
	quad.drawVertexes();
}
void MainGame::drawBoxBlurFilterPlane()
{
	transform.SetPos(glm::vec3(1.5f, 0.0f, 15.0f));
	transform.SetRot(glm::vec3(0.0f, 0.0f, 0.0f));
	transform.SetScale(glm::vec3(1.0f, 1.0f, 1.0f));

	boxBlurShader.Bind();
	linkBoxBlurShader(6);
	boxBlurShader.Update(transform, myCamera);

	texture4.Bind(0);
	quad.drawVertexes();
}
void MainGame::drawGaussianBlurFilterPlane()
{
	transform.SetPos(glm::vec3(-1.5f, 0.0f, 15.0f));
	transform.SetRot(glm::vec3(0.0f, 0.0f, 0.0f));
	transform.SetScale(glm::vec3(1.0f, 1.0f, 1.0f));

	gaussianShader.Bind();
	linkGaussianBlurShader(6);
	gaussianShader.Update(transform, myCamera);
	texture4.Bind(0);
	quad.drawVertexes();
}
void MainGame::drawKuwaharaFilterPlane()
{
	transform.SetPos(glm::vec3(-1.5f, 0.0f, 15.0f));
	transform.SetRot(glm::vec3(0.0f, 0.0f, 0.0f));
	transform.SetScale(glm::vec3(1.0f, 1.0f, 1.0f));

	kuwaharaShader.Bind();
	linkKuhawaraShader(5);
	kuwaharaShader.Update(transform, myCamera);
	texture4.Bind(0);
	quad.drawVertexes();
}

void MainGame::drawTRimExplodeObj()
{
	transform.SetPos(glm::vec3(-1.5f, 0.0f, -10.0f));
	transform.SetRot(glm::vec3(0.0f, time.getCurrentTime() * rotationSpeed * 0.01f, 0.0f));
	transform.SetScale(glm::vec3(1.0f, 1.0f, 1.0f));

	tRimExplodeShader.Bind();
	tRimExplodeShader.Update(transform, myCamera);
	linktRimExplodeShader();

	mesh4.Draw();
}
void MainGame::drawChromaticAbberationPlane() 
{
	transform.SetPos(glm::vec3(1.5f, 0.0f, -10.0f));
	transform.SetRot(glm::vec3(3.141592f, 0.0f, 3.141592f));
	transform.SetScale(glm::vec3(1.0f, 1.0f, 1.0f));

	chromaticAbberationShader.Bind();
	linkChromaticAbberation();
	chromaticAbberationShader.Update(transform, myCamera);
	texture4.Bind(0);
	quad.drawVertexes();
}

void MainGame::createGameObject()
{
	gameObject.init("..\\Resources\\Models\\Cube.obj", "..\\Resources\\Shaders\\DefaultShader.vert", "..\\Resources\\Shaders\\DefaultShader.frag", "..\\Resources\\Textures\\DefaultTexture.jpg");
}

void MainGame::drawGameObjects() {
	gameObject.Draw(myCamera);
}

void MainGame::drawObjects() {
	/*1st Geometry Shader
	* Texture + Explode Shader
	*/

	drawExplodeObj();

	/* Environment Mapping
	* 	
	*/

	drawEnvironmentMappingObjs();

	/* Extention 
	* Renders Normal Texture, then Box Blur, then a Gaussian Blur, then finally a Kuwahara Filter.
	*/
	// First Obj

	drawNormalPlane();
	
	// Second Obj

	//drawBoxBlurFilterPlane();

	// Third Obj
	
	//drawGaussianBlurFilterPlane();

	// Fourth Obj

	drawKuwaharaFilterPlane();

	// Misc
	/*2nd Geometry Shader
	* Rim + Toon + Explode Shader
	*/

	drawTRimExplodeObj();

	// Chromatic Abberation
	drawChromaticAbberationPlane();
	
}

// Draws game
void MainGame::drawGame()
{	
	// Clear display to blue background.
	display.clearDisplay(0.46f, 0.57f, 0.71f, 1.0f);

	//drawObjects();

	drawGameObjects();

	skybox.draw(&myCamera);

	display.swapBuffer();
}
#pragma region NotInUse

void MainGame::linkToonShader()
{
	toonShader.setMat4("modelMatrix", transform.GetModel());
	toonShader.setVec3("lightDir", glm::vec3(0.5f, 0.5f, 0.5f));
}

void MainGame::linkRimShader()
{
	rimShader.setMat4("modelMatrix", transform.GetModel());
	rimShader.setFloat("rimPower", 5.0f);
	rimShader.setVec3("rimColor", glm::vec3(0.8f, 0.0f, 0.0f));
	rimShader.setVec3("camPos", myCamera.getPos());
}

void MainGame::linkToonAndRimShader()
{
	try {
		toonAndRimShader.setMat4("modelMatrix", transform.GetModel());
		toonAndRimShader.setVec3("lightDir", glm::vec3(0.5f, 0.5f, 0.5f));
		toonAndRimShader.setFloat("rimPower", 5.0f);
		toonAndRimShader.setVec3("rimColor", glm::vec3(1.0f, 0.0f, 0.0f));
		toonAndRimShader.setVec3("camPos", myCamera.getPos());
	}
	catch (exception e) {
		cout << "broke";
	}
}
void MainGame::linkBumpShader()
{
	GLuint idOfUniform1 = glGetUniformLocation(bumpShader.getId(), "normalT");
	GLuint idOfUniform2 = glGetUniformLocation(bumpShader.getId(), "diffuse");

	glActiveTexture(GL_TEXTURE0); //set acitve texture unit
	glBindTexture(GL_TEXTURE_2D, texture2.getID());
	glUniform1i(idOfUniform2, 0);

	glActiveTexture(GL_TEXTURE1); //set acitve texture unit
	glBindTexture(GL_TEXTURE_2D, bumpTexture.getID());
	glUniform1i(idOfUniform1, 1);
	//try {
	//	bumpShader.setMat4("modelMatrix", transform.GetModel());
	//}
	//catch (exception e) {
	//	cout << "broke";
	//}
}

void MainGame::linkToffeeShader()
{
	// Define the model matrix (transforms from model space to world space)
	glm::mat4 model = transform.GetModel(); // Identity matrix

	// Define the view matrix (transforms from world space to camera space)
	glm::mat4 view = myCamera.getView();

	// Calculate the model-view matrix
	glm::mat4 modelView = view * model;
	toffeeShader.setMat3("normalMatrix", glm::transpose(glm::inverse(glm::mat3(modelView))));
	toffeeShader.setMat4("projectionMatrix", myCamera.getProjection());
	toffeeShader.setMat4("modelViewMatrix", modelView);
	toffeeShader.setFloat("time", time.getCurrentTime() * 0.01f);
}
void MainGame::linkSpecularShader(glm::vec3 colour)
{	// Define the model matrix (transforms from model space to world space)
	glm::mat4 model = transform.GetModel(); // Identity matrix

	// Define the view matrix (transforms from world space to camera space)
	glm::mat4 view = myCamera.getView();

	// Calculate the model-view matrix
	glm::mat4 modelView = view * model;
	specularShader.setMat3("normalMatrix", glm::transpose(glm::inverse(glm::mat3(modelView))));
	specularShader.setMat4("projectionMatrix", myCamera.getProjection());
	specularShader.setMat4("modelViewMatrix", modelView);
	specularShader.setVec3("albedo", colour);
}
void MainGame::linkToonSpecularShader(glm::vec3 colour)
{	// Define the model matrix (transforms from model space to world space)
	glm::mat4 model = transform.GetModel(); // Identity matrix

	// Define the view matrix (transforms from world space to camera space)
	glm::mat4 view = myCamera.getView();

	// Calculate the model-view matrix
	glm::mat4 modelView = view * model;
	toonSpecularShader.setMat3("normalMatrix", glm::transpose(glm::inverse(glm::mat3(modelView))));
	toonSpecularShader.setMat4("projectionMatrix", myCamera.getProjection());
	toonSpecularShader.setMat4("modelViewMatrix", modelView);
	toonSpecularShader.setVec3("albedo", colour);

	// Toon
	toonSpecularShader.setVec3("lightDir", glm::vec3(0.5f, 0.5f, 0.5f));
	toonSpecularShader.setVec3("camPos", myCamera.getPos());
}
bool MainGame::handleCollision(glm::vec3 mesh1Pos, float mesh1Rad, glm::vec3 mesh2Pos, float mesh2Rad)
{
	float distance = ((mesh2Pos.x - mesh1Pos.x) * (mesh2Pos.x - mesh1Pos.x) + (mesh2Pos.y - mesh1Pos.y) * (mesh2Pos.y - mesh1Pos.y) + (mesh2Pos.z - mesh1Pos.z) * (mesh2Pos.z - mesh1Pos.z));
	if (distance * distance < (mesh1Rad + mesh2Rad))
	{
		return true;
	}
	else
	{
		return false;
	}
}
void MainGame::checkCollisions() {
	// Check collision between mesh1 and mesh 3
	if (handleCollision(mesh1.getSpherePos(), mesh1.getSphereRadius(), mesh3.getSpherePos(), mesh3.getSphereRadius()))
	{
		// If previously not colliding
		if (!colliding1)
		{
			// AUDIO
			/*audioSource.playSFX(0);*/
			cout << "Collision between Mesh1 and Mesh3 \n";
			colliding1 = true;
		}
	}
	else
	{
		// If previously colliding
		if (colliding1)
		{
			cout << "Collision exit between Mesh1 and Mesh3 \n";
			colliding1 = false;
		}
	}
	// Check collision between mesh2 and mesh 3
	if (handleCollision(mesh2.getSpherePos(), mesh2.getSphereRadius(), mesh3.getSpherePos(), mesh3.getSphereRadius()))
	{
		// If previously not colliding
		if (!colliding2)
		{
			//audioSource.playSFX(0);
			cout << "Collision between Mesh2 and Mesh3 \n";
			colliding2 = true;
		}
	}
	else
	{
		// If previously colliding
		if (colliding2)
		{
			cout << "Collision exit between Mesh2 and Mesh3 \n";
			colliding2 = false;
		}
	}
}
#pragma endregion
