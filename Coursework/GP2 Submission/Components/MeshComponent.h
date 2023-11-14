#pragma once
#include "../ModelManager.h"

class MeshComponent {
public:
	MeshComponent(MeshType meshType, ModelManager& modelManager) 
		: myMeshType(meshType), myModelManager(modelManager){
		modelManager.loadModel(meshType);
	}

	void Draw() {
		myModelManager.draw(myMeshType);
	}
protected:
private:
	ModelManager& myModelManager;

	MeshType myMeshType;
};