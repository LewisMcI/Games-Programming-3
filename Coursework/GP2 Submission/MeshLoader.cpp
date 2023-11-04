#include "MeshLoader.h"
#include <vector>
#include <iostream>


MeshLoader::~MeshLoader()
{
	glDeleteVertexArrays(1, &vertexArrayObject); // delete arrays
}

void MeshLoader::Draw()
{
	// Bind VAO
	glBindVertexArray(vertexArrayObject);

	// Draw Elements
	glDrawArrays(GL_TRIANGLES, 0, drawCount);

	// Unbind
	glBindVertexArray(0);
}

void MeshLoader::loadModel(MeshType& meshType)
{
	// If model already loaded, use preloaded.
	if (loadedObjects.count(meshType)){
		initModel(loadedObjects[meshType]);
	}
	else {
		IndexedModel model = OBJModel(meshPaths[meshType]).toIndexedModel();
		loadedObjects.emplace(meshType, model);
		initModel(model);
	}
}
void MeshLoader::initModel(const IndexedModel& model)
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

