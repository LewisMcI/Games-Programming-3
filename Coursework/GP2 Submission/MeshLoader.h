#pragma once
#include <glm\glm.hpp>
#include <GL\glew.h>
#include <string>
#include <map>
#include "ModelLoader.h"

enum class MeshType { Cube, Draven, Ship };
class MeshLoader
{
public:
	MeshLoader() = default;
	~MeshLoader();
	void Draw();
	void loadModel(MeshType& meshType);
private:
	//enum
	//{
	//	POSITION_VERTEXBUFFER,
	//	TEXCOORD_VB,
	//	NORMAL_VB,
	//	INDEX_VB,
	//	NUM_BUFFERS
	//};
	//GLuint vertexArrayBuffers[NUM_BUFFERS];

	std::map<MeshType, std::string> meshPaths = {
	{MeshType::Cube, "..\\Resources\\Models\\Cube.obj"},
	{MeshType::Draven, "..\\Resources\\Models\\draven.obj"},
	{MeshType::Ship, "..\\Resources\\Models\\Ship.obj"}
	};

	std::vector<Model*> models;
};
