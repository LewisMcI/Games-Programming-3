#pragma once
#include "ModelManager.h"
#include <cstdio> // Include for FILE operations
#include <filesystem> // C++17 feature, include for directory operations
#include <sstream>
#include <iostream>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

namespace fs = std::filesystem;

void ModelManager::loadModel(MeshType& meshType) {
	// If model already loaded, return
	if (loadedMeshes.count(meshType))
		return;

    std::string meshPath = meshPaths[meshType];

    // Extracting filename from the given filePath
    fs::path originalPath(meshPath);
    std::string fileName = originalPath.filename().string();
    std::string binariesPath = "..\\Resources\\ModelBinaries\\" + fileName;

	// If model binaries exist
    if (std::filesystem::exists(binariesPath)) {
        std::cout << "\n__________________________________________________" << "\n";
        std::cout << "Binaries for model to load exists, LOADING: " << fileName << "\n";
        std::cout << "________________________________" << "\n";
        // Get Mesh
        std::vector<Mesh> newModel = RecreateMeshFromJson(LoadJsonFromFile(binariesPath));
        // Send data to buffer
        modelLoader.loadModel(newModel);
        // Add new mesh to list
        loadedMeshes.emplace(meshType, newModel);
        std::cout << "\n________________________________" << "\n";
    }
	// Load model
	else {
        std::cout << "Binaries do not exist for model" << "\n";
        std::cout << "________________________________" << "\n";
        // Load new mesh
		std::vector<Mesh> mesh = modelLoader.loadModel(meshPath.c_str());

        // Add new mesh to list
		loadedMeshes.emplace(meshType, mesh);
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

        // Write mesh to file.
        std::string json = SerializeMeshToJson(mesh);
        SaveJsonToFile(json, binariesPath);
        std::cout << "\n________________________________" << "\n";
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

        std::cout << "New time from serializing model = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
	}
}

void ModelManager::draw(MeshType& meshTypeToDraw) {
	for (const auto& pair : loadedMeshes) {
		// Get currentMeshType
		MeshType currMeshType = pair.first;
		// If we are not looking at the right model, move to next model
		if (currMeshType != meshTypeToDraw)
			continue;
		// Get list of meshes
		const std::vector<Mesh>& meshVector = pair.second;
		// Loop through all meshes in vector and draw
		for (const Mesh& mesh : meshVector) {
			glBindVertexArray(mesh.VAO);

			// Draw Elements
			glDrawElements(GL_TRIANGLES, (GLsizei)mesh.vertIndices.size(), GL_UNSIGNED_INT, 0);

			// Unbind
			glBindVertexArray(0);
		}
	}
}


// Function to serialize Mesh struct to JSON
std::string ModelManager::SerializeMeshToJson(const std::vector<Mesh>& meshes) {
    rapidjson::Document doc;
    doc.SetArray();

    std::cout << "\nSerializing Mesh struct to JSON..." << "\n\n";

    // Create rapidjson allocator
    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();
    int count = 0;
    for (const auto& mesh : meshes) {
        count++;
        std::cout << "Loading mesh data for mesh: " << count << "\n";
        rapidjson::Value meshObj(rapidjson::kObjectType);


        // Create rapidjson arrays for vectors
        rapidjson::Value vertPositions(rapidjson::kArrayType);
        for (const auto& vert : mesh.vertPositions) {
            rapidjson::Value vertJson(rapidjson::kArrayType);
            vertJson.PushBack(vert.x, allocator);
            vertJson.PushBack(vert.y, allocator);
            vertJson.PushBack(vert.z, allocator);
            vertPositions.PushBack(vertJson, allocator);
        }

        // Serialize vertNormals
        rapidjson::Value vertNormals(rapidjson::kArrayType);
        for (const auto& normal : mesh.vertNormals) {
            rapidjson::Value normalJson(rapidjson::kArrayType);
            normalJson.PushBack(normal.x, allocator);
            normalJson.PushBack(normal.y, allocator);
            normalJson.PushBack(normal.z, allocator);
            vertNormals.PushBack(normalJson, allocator);
        }

        // Serialize textCoords
        rapidjson::Value textCoords(rapidjson::kArrayType);
        for (const auto& texCoord : mesh.textCoords) {
            rapidjson::Value texCoordJson(rapidjson::kArrayType);
            texCoordJson.PushBack(texCoord.x, allocator);
            texCoordJson.PushBack(texCoord.y, allocator);
            textCoords.PushBack(texCoordJson, allocator);
        }

        // Serialize vertIndices
        rapidjson::Value vertIndices(rapidjson::kArrayType);
        for (const auto& index : mesh.vertIndices) {
            vertIndices.PushBack(index, allocator);
        }
        // Add arrays to the JSON object
        meshObj.AddMember("vertPositions", vertPositions, allocator);
        meshObj.AddMember("vertNormals", vertNormals, allocator);
        meshObj.AddMember("textCoords", textCoords, allocator);
        meshObj.AddMember("vertIndices", vertIndices, allocator);
        // Serialize textureHandle
        meshObj.AddMember("textureHandle", mesh.textureHandle, allocator);

        doc.PushBack(meshObj, allocator);
    }

    // Create a string buffer and writer for JSON serialization
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);

    std::cout << "Serialization to JSON completed." << "\n\n";

    // Return the serialized JSON as a string
    return buffer.GetString();
}

// Function to save JSON data to a file
bool ModelManager::SaveJsonToFile(const std::string& json, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return false;
    }

    file << json;
    file.close();
    std::cout << "Saved JSON data to file: " << filename << std::endl;
    return true;
}

std::string ModelManager::LoadJsonFromFile(const std::string& filename) {
    FILE* file = std::fopen(filename.c_str(), "r");
    if (file == nullptr) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return ""; // Return an empty string if file opening fails
    }

    // Find the file size
    std::fseek(file, 0, SEEK_END);
    long fileSize = std::ftell(file);
    std::rewind(file);

    // Allocate memory to read the file
    char* buffer = new char[fileSize + 1];
    std::fread(buffer, sizeof(char), fileSize, file);
    buffer[fileSize] = '\0'; // Null-terminate the string

    std::fclose(file);
    std::cout << "Loaded JSON data from file: " << filename << std::endl;

    std::string fileContent(buffer);
    delete[] buffer;

    return fileContent; // Return the content of the file as a string
}

std::vector<Mesh> ModelManager::RecreateMeshFromJson(const std::string& json) {
    std::vector<Mesh> meshes; // Create an empty Mesh object

    rapidjson::Document doc;
    doc.Parse(json.c_str());

    std::cout << "\nRecreating Mesh from JSON..." << "\n\n";

    if (doc.IsArray()) {
        for (rapidjson::SizeType meshIdx = 0; meshIdx < doc.Size(); ++meshIdx) {
            const rapidjson::Value& meshData = doc[meshIdx];

            Mesh mesh;

            // Access and extract JSON arrays for each member
            if (meshData.HasMember("vertPositions") && meshData["vertPositions"].IsArray()) {
                const rapidjson::Value& vertPositions = meshData["vertPositions"];
                for (rapidjson::SizeType i = 0; i < vertPositions.Size(); ++i) {
                    const rapidjson::Value& vert = vertPositions[i];
                    if (vert.IsArray() && vert.Size() == 3) {
                        glm::vec3 position(vert[0].GetFloat(), vert[1].GetFloat(), vert[2].GetFloat());
                        mesh.vertPositions.push_back(position);
                    }
                }
                std::cout << "Deserialized vertex positions" << std::endl;
            }

            // Extract and deserialize vertNormals
            if (meshData.HasMember("vertNormals") && meshData["vertNormals"].IsArray()) {
                const rapidjson::Value& vertNormals = meshData["vertNormals"];
                for (rapidjson::SizeType i = 0; i < vertNormals.Size(); ++i) {
                    const rapidjson::Value& normal = vertNormals[i];
                    if (normal.IsArray() && normal.Size() == 3) {
                        glm::vec3 normalVec(normal[0].GetFloat(), normal[1].GetFloat(), normal[2].GetFloat());
                        mesh.vertNormals.push_back(normalVec);
                    }
                }
                std::cout << "Deserialized vertex normals" << std::endl;
            }

            // Extract and deserialize textCoords
            if (meshData.HasMember("textCoords") && meshData["textCoords"].IsArray()) {
                const rapidjson::Value& textCoords = meshData["textCoords"];
                for (rapidjson::SizeType i = 0; i < textCoords.Size(); ++i) {
                    const rapidjson::Value& texCoord = textCoords[i];
                    if (texCoord.IsArray() && texCoord.Size() == 2) {
                        glm::vec2 texCoordVec(texCoord[0].GetFloat(), texCoord[1].GetFloat());
                        mesh.textCoords.push_back(texCoordVec);
                    }
                }
                std::cout << "Deserialized texture coordinates" << std::endl;
            }

            // Extract and deserialize vertIndices
            if (meshData.HasMember("vertIndices") && meshData["vertIndices"].IsArray()) {
                const rapidjson::Value& vertIndices = meshData["vertIndices"];
                for (rapidjson::SizeType i = 0; i < vertIndices.Size(); ++i) {
                    if (vertIndices[i].IsUint()) {
                        unsigned int index = vertIndices[i].GetUint();
                        mesh.vertIndices.push_back(index);
                    }
                }
                std::cout << "Deserialized vertex indicies" << std::endl;
            }

            // Extract and deserialize textureHandle
            if (meshData.HasMember("textureHandle") && meshData["textureHandle"].IsUint()) {
                mesh.textureHandle = meshData["textureHandle"].GetUint();
            }
            meshes.push_back(mesh);
        }
        std::cout << "Mesh recreation from JSON completed." << "\n\n";
    }
    else {
        std::cout << "JSON data does not contain an array of meshes." << "\n\n";
    }

    return meshes;
}