#pragma once
#include "../ModelManager.h"

class MeshComponent : public Component {
public:
	MeshComponent(MeshType meshType) 
		: myMeshType(meshType), myModelManager(ModelManager::getInstance()){
		myModelManager.loadModel(meshType);
	}

	void Draw() {
		myModelManager.draw(myMeshType);
	}

protected:
private:
	ModelManager& myModelManager;

	MeshType myMeshType;
};