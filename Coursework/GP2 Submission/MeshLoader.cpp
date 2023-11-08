#include "MeshLoader.h"
#include <vector>
#include <iostream>


MeshLoader::~MeshLoader()
{
	//glDeleteVertexArrays(1, &vertexArrayObject); // delete arrays
}

void MeshLoader::Draw()
{
	unsigned int vertexArrayObject = models[0]->meshList[0].VAO;
	// Bind VAO
	glBindVertexArray(vertexArrayObject);

	// Draw Elements
	glDrawElements(GL_TRIANGLES, (GLsizei)models[0]->meshList[0].vertIndices.size(), GL_UNSIGNED_INT, 0);

	// Unbind
	glBindVertexArray(0);
}

void MeshLoader::loadModel(MeshType& meshType)
{
	// Create new model
	Model* model = new Model(meshPaths[meshType].c_str());
	models.emplace_back(model);
	// Init
}
//void MeshLoader::initModel(const Model& model)
//{
//	drawCount = model.indices.size();
//
//	// Generate vertex array and store in VAO
//	glGenVertexArrays(1, &vertexArrayObject);
//	// Bind VAO
//	glBindVertexArray(vertexArrayObject);
//
//	// Generate buffers
//	glGenBuffers(NUM_BUFFERS, vertexArrayBuffers);
//	// Define type of data the buffer is
//	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[POSITION_VERTEXBUFFER]);
//	// Move data to GPU
//	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW);
//	// Num of Attribs
//	glEnableVertexAttribArray(0);
//	// Give OpenGL data on buffer
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
//
//	// Define type of data the buffer is
//	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[TEXCOORD_VB]);
//	// Move data to GPU
//	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW);
//	// Num of Attribs
//	glEnableVertexAttribArray(1);
//	// Give OpenGL data on buffer
//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
//
//	// Define type of data the buffer is
//	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[NORMAL_VB]);
//	// Move data to GPU
//	glBufferData(GL_ARRAY_BUFFER, model.normals.size() * sizeof(model.normals[0]), &model.normals[0], GL_STATIC_DRAW);
//	// Num of Attribs
//	glEnableVertexAttribArray(2);
//	// Give OpenGL data on buffer
//	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
//
//	// Define type of data the buffer is
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexArrayBuffers[INDEX_VB]); 
//	// Move data to GPU
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW);
//
//	// Unbind VAO
//	glBindVertexArray(0); 
//
//	// Cleanup
//	glDisableVertexAttribArray(0);
//	glDisableVertexAttribArray(1);
//}

