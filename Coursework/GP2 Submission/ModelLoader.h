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

class Model
{

private:
	Assimp::Importer importer;
	const aiScene* scene = nullptr;
	aiNode* rootNode = nullptr;

	struct Mesh {
		unsigned int VAO, VBO1, VBO2, VBO3, EBO;

		std::vector<glm::vec3> vertPositions;
		std::vector<glm::vec3> vertNormals;
		std::vector<glm::vec2> textCoords;
		std::vector<unsigned int> vertIndices;
		unsigned int texHandle;

		void Draw() {
			glBindVertexArray(VAO);

			// Draw Elements
			glDrawArrays(GL_TRIANGLES, 0, vertIndices.size());

			// Unbind
			glBindVertexArray(0);
		}
	};
	struct Texture {
		unsigned int textureId;
		std::string imageName;
	};

public:
	unsigned int numMeshes;
	std::vector<Mesh> meshList;
	std::vector<Texture> textureList;

	Model(const char* modelPath) {
		scene = importer.ReadFile(modelPath, aiProcess_JoinIdenticalVertices | aiProcess_Triangulate | aiProcess_FlipUVs);

		loadModel(modelPath);
	}

private:
	void loadModel(const char* modelPath) {
		if (!scene || !scene->mRootNode || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE)
			std::cout << "Assimp importer.ReadFile(Error) -- " << importer.GetErrorString() << "\n";

		else {
			numMeshes = scene->mNumMeshes;
			meshList.resize(numMeshes);

			aiMesh* mesh{};

			int indicesOffset = 0;
			// First loop cycles through all the models meshes
			for (unsigned int i = 0; i < numMeshes; ++i) {
				mesh = scene->mMeshes[i];

				aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

				// Second loop cycles throughh all textures
				//for (unsigned int texCount = 0; texCount < material->GetTextureCount(aiTextureType_DIFFUSE); ++texCount){
				//	aiString string;
				//	material->GetTexture(aiTextureType_DIFFUSE, texCount, &string);
				//	 
				//	int alreadyLoaded = isImageLoaded(string.C_Str());

				//	// Image not loaded
				//	if (alreadyLoaded == -1) {
				//		bool loadSuccess = false;
				//		unsigned int textureHandle = loadTextureImage(string.C_Str(), loadSuccess);

				//		if (loadSuccess) {
				//			Texture texture;
				//			texture.imageName = string.C_Str();
				//			texture.textureId = textureHandle;
				//			
				//			textureList.push_back(texture);
				//			meshList[i].texHandle = textureHandle;
				//		}
				//	}
				//	// Use existing image
				//	else {
				//		meshList[i].texHandle = alreadyLoaded;
				//	}
				//}

				// Third loop cycles through all mesh vertices
				for (unsigned int i2 = 0; i2 < mesh->mNumVertices; ++i2) {
					glm::vec3 position{};
					position.x = mesh->mVertices[i2].x;
					position.y = mesh->mVertices[i2].y;
					position.z = mesh->mVertices[i2].z;

					meshList[i].vertPositions.push_back(position);

					if (mesh->HasNormals()) {
						glm::vec3 normal{};
						normal.x = mesh->mNormals[i2].x;
						normal.y = mesh->mNormals[i2].y;
						normal.z = mesh->mNormals[i2].z;

						meshList[i].vertNormals.push_back(normal);
					}
					else
						meshList[i].vertNormals.push_back(glm::vec3(0.0f));

					if (mesh->HasTextureCoords(0)) {
						glm:: vec2 texCoords{};
						texCoords.x = mesh->mTextureCoords[0][i2].x;
						texCoords.y = mesh->mTextureCoords[0][i2].y;
						meshList[i].textCoords.push_back(texCoords);
					}
					else
						meshList[i].textCoords.push_back(glm::vec2(0.0f));
				}

				// Fourth loop cycles through all mesh indices
				for (unsigned int i3 = 0; i3 < mesh->mNumFaces; ++i3)
					for (unsigned int i4 = 0; i4 < mesh->mFaces[i3].mNumIndices; ++i4)
						meshList[i].vertIndices.push_back(mesh->mFaces[i3].mIndices[i4] + indicesOffset);

				// Setup VAO VBO and EBO.
				setBufferData(i);
			}
		}
	}

	void setBufferData(unsigned int index) {
		glGenVertexArrays(1, &meshList[index].VAO);
		// Could use one VBO and usue glVertexAttrib pointer offset
		glGenBuffers(1, &meshList[index].VBO1);
		glGenBuffers(1, &meshList[index].VBO2);
		glGenBuffers(1, &meshList[index].VBO3);
		glGenBuffers(1, &meshList[index].EBO);

		glBindVertexArray(meshList[index].VAO);

		// Vertex Positions
		glBindBuffer(GL_ARRAY_BUFFER, meshList[index].VBO1);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * meshList[index].vertPositions.size(), &meshList[index].vertPositions[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

		// Texture Coordinates
		glBindBuffer(GL_ARRAY_BUFFER, meshList[index].VBO3);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * meshList[index].textCoords.size(), &meshList[index].textCoords[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

		// Vertex Normals
		glBindBuffer(GL_ARRAY_BUFFER, meshList[index].VBO2);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * meshList[index].vertNormals.size(), &meshList[index].vertNormals[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

		// Indices for glDrawElements()
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshList[index].EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * meshList[index].vertIndices.size(), &meshList[index].vertIndices[0], GL_STATIC_DRAW);

		glBindVertexArray(0);

		// Cleanup
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
	}
	int isImageLoaded(std::string fileName) {
		for (unsigned int i = 0; i < textureList.size(); ++i) {
			if (fileName.compare(textureList[i].imageName) == 0)
				return textureList[i].textureId;
		}
		return -1;
	}

	//unsigned int loadTextureImage(std::string fileName, bool& loadComplete) {
	//	// stbi_set_flip_vertically_on_load(1); // If image is upside down


	//	int width, height, numOfComponents;
	//	// Load Image
	//	unsigned char* data = stbi_load((fileName).c_str(), &width, &height, &numOfComponents, 0);

	//	// If data could not be loaded
	//	if (data == NULL)
	//	{	
	//		loadComplete = false;
	//		stbi_image_free(data);
	//		std::cerr << "Image Loaded: " << fileName << std::endl;
	//		return 0;
	//	}

	//	GLenum format{};
	//	if (numOfComponents == 1)
	//		format = GL_RED;
	//	else if (numOfComponents == 3)
	//		format = GL_RGB;
	//	else if (numOfComponents == 4)
	//		format = GL_RGBA;

	//	GLuint textureId;

	//	// Generates texture names
	//	glGenTextures(1, &textureId);

	//	// Bind the newly created textureHandler
	//	glBindTexture(GL_TEXTURE_2D, textureId);

	//	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	//	// Specify the 2D texture image (Target, Mipmapping Level, Internal Format, Width, Height, Border Size, Format, Type, Image Data)
	//	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	//	glGenerateMipmap(GL_TEXTURE_2D);
	//	// Wrap Textures with Width and Height
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//	// Enable Linear Filtering for minification and magnification
	//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	//	loadComplete = true;
	//	// Free memory allocated by STBI_LOAD
	//	stbi_image_free(data);
	//	std::cout << "Image Loaded: " << fileName << "\n";
	//}
};