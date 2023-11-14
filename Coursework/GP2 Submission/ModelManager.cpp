#pragma once
#include "ModelManager.h"

void ModelManager::loadModel(MeshType& meshType) {
	// If model already loaded, return
	if (loadedMeshes.count(meshType))
		return;

	// If model binaries exist
	if (lookForModelBinary(meshPaths[meshType]))
	{

	}
	// Load model
	else {
		std::vector<Mesh> mesh = modelLoader.loadModel(meshPaths[meshType].c_str());
		loadedMeshes.emplace(meshType, mesh);
		writeModelBinary(meshType);
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
bool ModelManager::lookForModelBinary(std::string meshPath)
{
	bool file_not_found = false;

	std::ifstream vert_data; // Read data.

	std::size_t position = meshPath.find_last_of("\\");
	std::string model_name = meshPath.substr(position + 1);

	vert_data.open("Model Data/" + model_name + "_vert_positions.bin", std::ios::in);
	std::cout << "   Detecting: " << model_name + "_vert_positions.bin: " << vert_data.is_open() << "\n";
	if (!vert_data.is_open()) { file_not_found = true; }
	vert_data.close();

	vert_data.open("Model Data/" + model_name + "_vert_normals.bin", std::ios::in);
	std::cout << "   Detecting: " << model_name + "_vert_normals.bin: " << vert_data.is_open() << "\n";
	if (!vert_data.is_open()) { file_not_found = true; }
	vert_data.close();

	vert_data.open("Model Data/" + model_name + "_tex_coords.bin", std::ios::in);
	std::cout << "   Detecting: " << model_name + "_tex_coords.bin: " << vert_data.is_open() << "\n";
	if (!vert_data.is_open()) { file_not_found = true; }
	vert_data.close();

	vert_data.open("Model Data/" + model_name + "_vert_indices.bin", std::ios::in);
	std::cout << "   Detecting: " << model_name + "_vert_indices.bin: " << vert_data.is_open() << "\n";
	if (!vert_data.is_open()) { file_not_found = true; }
	vert_data.close();

	vert_data.open("Model Data/" + model_name + "_mesh_num.bin", std::ios::in);
	std::cout << "   Detecting: " << model_name + "_mesh_num.bin: " << vert_data.is_open() << "\n";
	if (!vert_data.is_open()) { file_not_found = true; }
	vert_data.close();

	vert_data.open("Model Data/" + model_name + "_sampler_array_pos.bin", std::ios::in);
	std::cout << "   Detecting: " << model_name + "_sampler_array_pos.bin: " << vert_data.is_open() << "\n";
	if (!vert_data.is_open()) { file_not_found = true; }
	vert_data.close();

	vert_data.open("Model Data/" + model_name + "_image_names.txt", std::ios::in);
	std::cout << "   Detecting: " << model_name + "_image_names.txt: " << vert_data.is_open() << "\n";
	if (!vert_data.is_open()) { file_not_found = true; }
	vert_data.close();

	if (file_not_found)
		return false;

	return true;
}
//
//void ModelManager::writeModelBinary(MeshType& meshType)
//{
//	std::string meshPath = meshPaths[meshType];
//	std::string file_name;
//	std::ofstream vert_data; // Write data.
//
//	std::size_t position = meshPath.find_last_of("\\");
//	std::string model_name = meshPath.substr(position + 1);
//
//	file_name = "Model Data/" + model_name + "_vert_positions.bin";
//	vert_data.open(file_name, std::ios::out | std::ios::binary);
//	vert_data.write(reinterpret_cast<char*>(&meshes_5VBO_combined.vert_positions[0]), meshes_5VBO_combined.vert_positions.size() * 3 * sizeof(float));
//	vert_data.close();
//
//	file_name = "Model Data/" + model_name + "_vert_normals.bin";
//	vert_data.open(file_name, std::ios::out | std::ios::binary);
//	vert_data.write(reinterpret_cast<char*>(&meshes_5VBO_combined.vert_normals[0]), meshes_5VBO_combined.vert_normals.size() * 3 * sizeof(float));
//	vert_data.close();
//
//	file_name = "Model Data/" + model_name + "_tex_coords.bin";
//	vert_data.open(file_name, std::ios::out | std::ios::binary);
//	vert_data.write(reinterpret_cast<char*>(&meshes_5VBO_combined.tex_coords[0]), meshes_5VBO_combined.tex_coords.size() * 2 * sizeof(float));
//	vert_data.close();
//
//	file_name = "Model Data/" + model_name + "_vert_indices.bin";
//	vert_data.open(file_name, std::ios::out | std::ios::binary);
//	vert_data.write(reinterpret_cast<char*>(&meshes_5VBO_combined.vert_indices[0]), meshes_5VBO_combined.vert_indices.size() * sizeof(unsigned int));
//	vert_data.close();
//
//	file_name = "Model Data/" + model_name + "_mesh_num.bin";
//	vert_data.open(file_name, std::ios::out | std::ios::binary);
//	vert_data.write(reinterpret_cast<char*>(&meshes_5VBO_combined.mesh_num[0]), meshes_5VBO_combined.mesh_num.size() * sizeof(unsigned int));
//	vert_data.close();
//
//	file_name = "Model Data/" + model_name + "_sampler_array_pos.bin";
//	vert_data.open(file_name, std::ios::out | std::ios::binary);
//	vert_data.write(reinterpret_cast<char*>(&meshes_5VBO_combined.sampler_array_pos[0]), meshes_5VBO_combined.sampler_array_pos.size() * sizeof(unsigned int));
//	vert_data.close();
//
//	std::string names_to_file;
//	//for (unsigned int i = 0; i < texture_list.size(); ++i)
//	//{
//	//	names_to_file += texture_list[i].image_name;
//	//	names_to_file += "\n";
//	//}
//	// file_name = "Model Data/" + model_name + "_image_names.bin";
//	// vert_data.open(file_name, std::ios::out | std::ios::binary);
//	file_name = "Model Data/" + model_name + "_image_names.txt";
//	vert_data.open(file_name, std::ios::out);
//	vert_data.write(reinterpret_cast<char*>(&names_to_file[0]), names_to_file.size() * sizeof(char));
//	vert_data.close();
//}

//
//void ModelManager::readModelBinary(std::string meshPath)
//{
//	std::string file_name;
//	std::ifstream vert_data; // Read data.
//	size_t vector_bytes_size = 0;
//	size_t vector_index_size = 0;
//
//	std::size_t position = meshPath.find_last_of("\\");
//	std::string model_name = meshPath.substr(position + 1);
//	file_name = model_name;
//
//	// -------------------
//
//	file_name = "Model Data/" + model_name + "_vert_positions.bin";
//	vert_data.open(file_name, std::ios::in | std::ios::binary | std::ios::ate);
//
//	vector_bytes_size = vert_data.tellg();
//	vector_index_size = vector_bytes_size / (3 * sizeof(float));
//
//	meshes_5VBO_combined.vert_positions.resize(vector_index_size);
//
//	vert_data.seekg(std::ios::beg);
//	vert_data.read(reinterpret_cast<char*>(&meshes_5VBO_combined.vert_positions[0]), vector_bytes_size);
//	vert_data.close();
//
//	// -------------------
//
//	file_name = "Model Data/" + model_name + "_vert_normals.bin";
//	vert_data.open(file_name, std::ios::in | std::ios::binary | std::ios::ate);
//
//	vector_bytes_size = vert_data.tellg();
//	vector_index_size = vector_bytes_size / (3 * sizeof(float));
//
//	meshes_5VBO_combined.vert_normals.resize(vector_index_size);
//
//	vert_data.seekg(std::ios::beg);
//	vert_data.read(reinterpret_cast<char*>(&meshes_5VBO_combined.vert_normals[0]), vector_bytes_size);
//	vert_data.close();
//
//	// -------------------
//
//	file_name = "Model Data/" + model_name + "_tex_coords.bin";
//	vert_data.open(file_name, std::ios::in | std::ios::binary | std::ios::ate);
//
//	vector_bytes_size = vert_data.tellg();
//	vector_index_size = vector_bytes_size / (2 * sizeof(float));
//
//	meshes_5VBO_combined.tex_coords.resize(vector_index_size);
//
//	vert_data.seekg(std::ios::beg);
//	vert_data.read(reinterpret_cast<char*>(&meshes_5VBO_combined.tex_coords[0]), vector_bytes_size);
//	vert_data.close();
//
//	// -------------------
//
//	file_name = "Model Data/" + model_name + "_vert_indices.bin";
//	vert_data.open(file_name, std::ios::in | std::ios::binary | std::ios::ate);
//
//	vector_bytes_size = vert_data.tellg();
//	vector_index_size = vector_bytes_size / sizeof(unsigned int);
//
//	meshes_5VBO_combined.vert_indices.resize(vector_index_size);
//
//	vert_data.seekg(std::ios::beg);
//	vert_data.read(reinterpret_cast<char*>(&meshes_5VBO_combined.vert_indices[0]), vector_bytes_size);
//	vert_data.close();
//
//	// -------------------
//
//	file_name = "Model Data/" + model_name + "_mesh_num.bin";
//	vert_data.open(file_name, std::ios::in | std::ios::binary | std::ios::ate);
//
//	vector_bytes_size = vert_data.tellg();
//	vector_index_size = vector_bytes_size / sizeof(unsigned int);
//
//	meshes_5VBO_combined.mesh_num.resize(vector_index_size);
//
//	vert_data.seekg(std::ios::beg);
//	vert_data.read(reinterpret_cast<char*>(&meshes_5VBO_combined.mesh_num[0]), vector_bytes_size);
//	vert_data.close();
//
//	// -------------------
//
//	file_name = "Model Data/" + model_name + "_sampler_array_pos.bin";
//	vert_data.open(file_name, std::ios::in | std::ios::binary | std::ios::ate);
//
//	vector_bytes_size = vert_data.tellg();
//	vector_index_size = vector_bytes_size / sizeof(unsigned int);
//
//	meshes_5VBO_combined.sampler_array_pos.resize(vector_index_size);
//
//	vert_data.seekg(std::ios::beg);
//	vert_data.read(reinterpret_cast<char*>(&meshes_5VBO_combined.sampler_array_pos[0]), vector_bytes_size);
//	vert_data.close();
//
//	// -------------------		
//
//		// file_name = "Model Data/" + model_name + "_image_names.bin";
//		// vert_data.open(file_name, std::ios::in | std::ios::binary | std::ios::ate);
//	file_name = "Model Data/" + model_name + "_image_names.txt";
//	vert_data.open(file_name, std::ios::in | std::ios::ate);
//
//	vector_bytes_size = vert_data.tellg();
//	vector_index_size = vector_bytes_size / sizeof(char);
//
//	std::string names_from_file;
//	names_from_file.resize(vector_index_size);
//
//	vert_data.seekg(std::ios::beg);
//	vert_data.read(reinterpret_cast<char*>(&names_from_file[0]), vector_bytes_size);
//	vert_data.close();
//
//	const char* all_names = names_from_file.c_str();
//
//	std::string single_name;
//	for (unsigned int i = 0; i < names_from_file.size(); ++i)
//	{
//		if (*all_names != '\n')
//			single_name += *all_names;
//		else
//		{
//			Texture texture;
//			texture.image_name = single_name;
//			texture.tex_handle = 0; // Temporary value. Gets overridden in: load_file_name_images()
//
//			meshes_5VBO_combined.texture_list.push_back(texture);
//			single_name.clear();
//		}
//		++all_names;
//	}
//	/*for (unsigned int i = 0; i < meshes_5VBO_combined.texture_list.size(); ++i)
//		std::cout << "\n Retrieved names: " << meshes_5VBO_combined.texture_list[i].image_name << "\n";*/
//}
