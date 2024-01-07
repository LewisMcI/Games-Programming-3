#pragma once
#include "../Components/MaterialComponent.h"
#include "../Components/MeshComponent.h"
#include "../Scene/SceneManager.h"
#include "Entity.h"
#include "../Components/Player.h"

class GameScene {
public:
	GameScene() = default;
	~GameScene() = default;

	void Load();
protected:
private:
	void createPlayer(ShaderType shaderType, TextureType textureType, MeshType meshType);
	void createAsteroidSpawner();
};