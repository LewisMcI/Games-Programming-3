#pragma once
#include "Component.h"
#include "../Scene/Scene.h"

class AsteroidMovement : public Component {
public:
	AsteroidMovement(){
		targetDir = glm::normalize(glm::vec3(getRandomFloat(HI, LO),
			getRandomFloat(HI, LO),
			getRandomFloat(HI, LO)));
	}

	~AsteroidMovement() = default;

	void onUpdate();

protected:
private:
	float getRandomFloat(float high, float low) {
		return low + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (high - low)));
	}

	glm::vec3 targetDir;
	float HI = 100.0f;
	float LO = -100.0f;
};