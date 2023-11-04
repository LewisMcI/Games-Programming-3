#pragma once
#include <glm\glm.hpp>
#include <GL\glew.h>
#include <string>
#include <map>
#include "ObjectLoader.h"
struct Sphere
{
public:

	Sphere() {}

	glm::vec3 GetPos() { return pos; }
	float GetRadius() { return radius; }

	void SetPos(glm::vec3 pos)
	{
		this->pos = pos;
	}

	void SetRadius(float radius)
	{
		this->radius = radius;
	}

private:
	glm::vec3 pos;
	float radius;
};

class Vertex
{
public:
	Vertex(const glm::vec3& pos, const glm::vec2& texCoord)
	{
		this->pos = pos;
		this->texCoord = texCoord;
		this->normal = normal;
	}

	glm::vec3* GetPos() { return &pos; }
	glm::vec2* GetTexCoord() { return &texCoord; }
	glm::vec3* GetNormal() { return &normal; }

	glm::vec3 pos;
	glm::vec2 texCoord;
	glm::vec3 normal;

protected:
private:

};

enum class MeshType { Cube, Draven, Ship };
class MeshLoader
{
public:
	MeshLoader() = default;
	~MeshLoader();
	void Draw();
	void loadModel(MeshType& meshType);
private:
	enum
	{
		POSITION_VERTEXBUFFER,
		TEXCOORD_VB,
		NORMAL_VB,
		INDEX_VB,
		NUM_BUFFERS
	};

	std::map<MeshType, std::string> meshPaths = {
	{MeshType::Cube, "..\\Resources\\Models\\Cube.obj"},
	{MeshType::Draven, "..\\Resources\\Models\\draven.obj"},
	{MeshType::Ship, "..\\Resources\\Models\\Ship.obj"}
	};
	std::map<MeshType, IndexedModel> loadedObjects;

	void initModel(const IndexedModel& model);

	GLuint vertexArrayObject;

	GLuint vertexArrayBuffers[NUM_BUFFERS]; 
	
	unsigned int drawCount = 0;	
};
