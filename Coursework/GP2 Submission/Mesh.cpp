#include "Mesh.h"
#include <vector>


Mesh::Mesh() 
{
	drawCount = 0;
	GLuint vertexArrayObject();
	GLuint vertexArrayBuffers[NUM_BUFFERS]{};
}
void Mesh::loadVertexs(Vertex* vertices, unsigned int numVertices)
{
	drawCount = numVertices;

	glGenVertexArrays(1, &vertexArrayObject); //generate a vertex array and store it in the VAO
	glBindVertexArray(vertexArrayObject); //bind the VAO (any operation that works on a VAO will work on our bound VAO - binding)

	std::vector<glm::vec3> positions; //holds the position data
	std::vector<glm::vec2> textCoords; //holds the texture coordinate data

	positions.reserve(numVertices); // reserve the all the space needed to hold our data
	textCoords.reserve(numVertices);

	for (int i = 0; i < numVertices; i++)
	{
		positions.push_back(vertices[i].pos); //store our array of vertex positon into a list vec3 positions
		textCoords.push_back(vertices[i].texCoord);
	}

	glGenBuffers(NUM_BUFFERS, vertexArrayBuffers); //generate our buffers based of our array of data/buffers - GLuint vertexArrayBuffers[NUM_BUFFERS];
	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[POSITION_VERTEXBUFFER]); //tell opengl what type of data the buffer is (GL_ARRAY_BUFFER), and pass the data
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW); //move the data to the GPU - type of data, size of data, starting address (pointer) of data, where do we store the data on the GPU (determined by type)

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[TEXCOORD_VB]); //tell opengl what type of data the buffer is (GL_ARRAY_BUFFER), and pass the data
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(textCoords[0]), &textCoords[0], GL_STATIC_DRAW); //move the data to the GPU - type of data, size of data, starting address (pointer) of data, where do we store the data on the GPU

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0); // unbind our VAO
}

void Mesh::init(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices)
{
	IndexedModel model;

	for (unsigned int i = 0; i < numVertices; i++)
	{
		model.positions.push_back(*vertices[i].GetPos());
		model.texCoords.push_back(*vertices[i].GetTexCoord());
		model.normals.push_back(*vertices[i].GetNormal());
	}

	for (unsigned int i = 0; i < numIndices; i++)
		model.indices.push_back(indices[i]);

	initModel(model);
}

void Mesh::initModel(const IndexedModel& model)
{
	drawCount = model.indices.size();

	// Generate vertex array and store in VAO
	glGenVertexArrays(1, &vertexArrayObject);
	// Bind VAO
	glBindVertexArray(vertexArrayObject);

	// Generate buffers
	glGenBuffers(NUM_BUFFERS, vertexArrayBuffers);
	// Define type of data the buffer is
	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[POSITION_VERTEXBUFFER]);
	// Move data to GPU
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW);
	// Num of Attribs
	glEnableVertexAttribArray(0);
	// Give OpenGL data on buffer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Define type of data the buffer is
	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[TEXCOORD_VB]);
	// Move data to GPU
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW);
	// Num of Attribs
	glEnableVertexAttribArray(1);
	// Give OpenGL data on buffer
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	// Define type of data the buffer is
	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[NORMAL_VB]);
	// Move data to GPU
	glBufferData(GL_ARRAY_BUFFER, model.normals.size() * sizeof(model.normals[0]), &model.normals[0], GL_STATIC_DRAW);
	// Num of Attribs
	glEnableVertexAttribArray(2);
	// Give OpenGL data on buffer
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Define type of data the buffer is
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexArrayBuffers[INDEX_VB]); 
	// Move data to GPU
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW);

	// Unbind VAO
	glBindVertexArray(0); 

	// Cleanup
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

void Mesh::loadModel(const std::string& filename)
{
	IndexedModel model = OBJModel(filename).ToIndexedModel();
	initModel(model);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vertexArrayObject); // delete arrays
}

void Mesh::drawVertexes()
{
	glBindVertexArray(vertexArrayObject);
	glDrawArrays(GL_TRIANGLES, 0, drawCount);
	glBindVertexArray(0);
}

void Mesh::Draw()
{
	// Bind VAO
	glBindVertexArray(vertexArrayObject);

	// Draw Elements
	glDrawArrays(GL_TRIANGLES, 0, drawCount);

	// Unbind
	glBindVertexArray(0);
}
void Mesh::updateSphere(glm::vec3 pos, float radius)
{
	// Set new position and radius
	collisionSphere.SetPos(pos);
	collisionSphere.SetRadius(radius);
}
