#pragma once
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include "../Display.h" 
#include "../Time.h"
#include "../SkyBox.h"
#include "../GameObject.h"
#include "../Player.h"
#include <chrono>
#include "../Components/MeshComponent.h"
#include "Entity.h";
#include "../Components/MaterialComponent.h"
#include "../ModelManager.h"
#include "../Components/AsteroidSpawner.h"
#include "SceneManager.h"

class GameScene {
public:
	GameScene() = default;
	~GameScene() = default;

	void Load();
protected:
private:
	void createPlayer(ShaderType shaderType, TextureType textureType, MeshType meshType);
};