#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <GL/glew.h>
#include <cassert>
#include <iostream>
#include <map>
#include <fstream>
#include "../Other/GlobalVariables.h"


struct Mesh {
	enum
	{
		POSITION_VERTEXBUFFER,
		TEXCOORD_VB,
		NORMAL_VB,
		NUM_BUFFERS
	};

	GLuint VAO, EBO;
	GLuint vertexArrayBuffers[static_cast<size_t>(NUM_BUFFERS)];

	std::vector<glm::vec3> vertPositions;
	std::vector<glm::vec3> vertNormals;
	std::vector<glm::vec2> textCoords;
	std::vector<unsigned int> vertIndices;
};

struct Model {
	std::vector<Mesh> meshList;
};

class ModelLoader
{
public:
	ModelLoader() = default;

	Model loadModel(const char* modelPath) {
		Model newModel;
		// Load Model
		modelData = importer.ReadFile(modelPath, aiProcess_JoinIdenticalVertices | aiProcess_Triangulate | aiProcess_FlipUVs);

		// If model failed to load || model has no meshes || model encountered an issue
		if (!modelData || !modelData->mRootNode || modelData->mFlags & AI_SCENE_FLAGS_INCOMPLETE) {
			if (USE_ERROR_DEBUGGING)
				std::cerr << "Could not load model at: " << modelPath << ": Model has no meshes, encountered an issue or failed during loading." << std::endl;
			return newModel;
		}

		// Model is fine to parse
		else {
			unsigned int numMeshes = modelData->mNumMeshes;
			newModel.meshList.resize(numMeshes);

			aiMesh* mesh{};
			auto meshes = modelData->mMeshes;

			// Cycle through all the model meshes
			for (unsigned int i = 0; i < numMeshes; ++i) {
				mesh = modelData->mMeshes[i];

				unsigned int numVertices = mesh->mNumVertices;
				// Cycle through mesh vertices
				for (unsigned int j = 0; j < numVertices; ++j) {
					// Add Positions
					glm::vec3 position{};
					position.x = mesh->mVertices[j].x;
					position.y = mesh->mVertices[j].y;
					position.z = mesh->mVertices[j].z;
					
					newModel.meshList[i].vertPositions.push_back(position);

					// Add Normals
					if (mesh->HasNormals()) {
						glm::vec3 normal{};
						normal.x = mesh->mNormals[j].x;
						normal.y = mesh->mNormals[j].y;
						normal.z = mesh->mNormals[j].z;

						newModel.meshList[i].vertNormals.push_back(normal);
					}
					else
						newModel.meshList[i].vertNormals.push_back(glm::vec3(0.0f));

					// Add Texture Coordinates
					if (mesh->HasTextureCoords(0)) {
						glm::vec2 texCoords{};
						texCoords.x = mesh->mTextureCoords[0][j].x;
						texCoords.y = mesh->mTextureCoords[0][j].y;
						newModel.meshList[i].textCoords.push_back(texCoords);
					}
					else
						newModel.meshList[i].textCoords.push_back(glm::vec2(0.0f));
				}

				// Cycle through mesh indices
				for (unsigned int j = 0; j < mesh->mNumFaces; ++j)
					for (unsigned int k = 0; k < mesh->mFaces[j].mNumIndices; ++k)
						newModel.meshList[i].vertIndices.push_back(mesh->mFaces[j].mIndices[k]);

				// Setup VAO VBO and EBO.
				setBufferData(newModel.meshList[i]);
			}
		}	
		return newModel;
	}

	void loadModel(Model& model) {
		for (size_t i = 0; i < model.meshList.size(); i++)
		{
			setBufferData(model.meshList[i]);
		}
	}
private:
	void setBufferData(Mesh& mesh) {
		glGenVertexArrays(1, &mesh.VAO);
		// Could use one VBO and usue glVertexAttrib pointer offset
		glGenBuffers(4, mesh.vertexArrayBuffers); //generate our buffers based of our array of data/buffers - GLuint vertexArrayBuffers[NUM_BUFFERS];
		glGenBuffers(1, &mesh.EBO);

		glBindVertexArray(mesh.VAO);

		// Vertex Positions

		glBindBuffer(GL_ARRAY_BUFFER, mesh.vertexArrayBuffers[mesh.POSITION_VERTEXBUFFER]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * mesh.vertPositions.size(), &mesh.vertPositions[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(mesh.POSITION_VERTEXBUFFER);
		glVertexAttribPointer(mesh.POSITION_VERTEXBUFFER, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

		// Texture Coordinates
		glBindBuffer(GL_ARRAY_BUFFER, mesh.vertexArrayBuffers[mesh.TEXCOORD_VB]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * mesh.textCoords.size(), &mesh.textCoords[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(mesh.TEXCOORD_VB);
		glVertexAttribPointer(mesh.TEXCOORD_VB, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

		// Vertex Normals
		glBindBuffer(GL_ARRAY_BUFFER, mesh.vertexArrayBuffers[mesh.NORMAL_VB]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * mesh.vertNormals.size(), &mesh.vertNormals[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(mesh.NORMAL_VB);
		glVertexAttribPointer(mesh.NORMAL_VB, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

		// Indices for glDrawElements()
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * mesh.vertIndices.size(), &mesh.vertIndices[0], GL_STATIC_DRAW);

		glBindVertexArray(0);

		// Cleanup
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
	}

	Assimp::Importer importer;
	// Generally referred to as a Scene using assimp, however I feel model better describes its purpose in the 
	// case of this engine.
	const aiScene* modelData = nullptr;
	aiNode* rootNode = nullptr;

};