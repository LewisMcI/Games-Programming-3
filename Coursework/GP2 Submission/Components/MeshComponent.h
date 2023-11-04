#pragma once
#include "../MeshLoader.h"

class MeshComponent {
public:
	MeshComponent(MeshType meshType, MeshLoader& meshLoader) : mesh(meshLoader){
		mesh.loadModel(meshType);
	}

	void Draw() {
		mesh.Draw();
	}
protected:
private:
	MeshLoader& mesh;
};