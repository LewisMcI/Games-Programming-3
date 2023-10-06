#pragma once
#include <glm\glm.hpp>
#include <GL\glew.h>
#include <string>
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

class Mesh
{
public:
	Mesh();
	void loadVertexs(Vertex* vertices, unsigned int numVertices);
	void init(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
	~Mesh();

	void drawVertexes();

	void Draw();
	void loadModel(const std::string& filename);
	void initModel(const IndexedModel& model);

	void updateSphere(glm::vec3 pos, float radius);
	glm::vec3 getSpherePos() { return collisionSphere.GetPos(); }
	float getSphereRadius() { return collisionSphere.GetRadius(); }
private:

	enum
	{
		POSITION_VERTEXBUFFER,
		TEXCOORD_VB,
		NORMAL_VB,
		INDEX_VB,
		NUM_BUFFERS
	};
	// Mesh
	Sphere collisionSphere;
	// VAO
	GLuint vertexArrayObject;
	// Array of Buffers
	GLuint vertexArrayBuffers[NUM_BUFFERS]; 
	// VAO Draw Count
	unsigned int drawCount;
};
