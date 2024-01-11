#pragma once
#include "Component.h"
#include <glm/glm.hpp>

class Collider : public Component {
public:
	Collider(glm::vec3 size = glm::vec3(0.0f)) : size(size) {

	}
	glm::vec3 size;
protected:
private:
};