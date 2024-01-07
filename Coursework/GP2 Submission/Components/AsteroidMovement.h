#pragma once
#include "Component.h"
#include "TransformComponent.h"
#include "../Scene/Entity.h"

class AsteroidMovement : public Component {
public:
	void onUpdate() {
		std::cout << "Test";
	}
protected:
private:
	std::unique_ptr<TransformComponent> transform = nullptr;
	bool flag = false;
};