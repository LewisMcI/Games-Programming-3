#pragma once
#include "Component.h"
#include "../Scene/Scene.h"

class AsteroidMovement : public Component {
public:
	AsteroidMovement(Entity& player) : player(player){

	}
	~AsteroidMovement() = default;

	void onUpdate();

protected:
private:
	Entity& player;
};