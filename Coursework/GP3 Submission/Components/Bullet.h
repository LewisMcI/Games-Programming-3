#pragma once
#include "Component.h"
#include <glm/detail/type_vec.hpp>
#include "TransformComponent.h"
#include "../Base Scripts/Time.h"

class Bullet : public Component {
public:
	Bullet(TransformComponent& transform, glm::vec3 distance) : transform(transform), dir(glm::normalize(distance)) {
		bulletEndLife = Time::getInstance().getCurrentTime() + bulletLife;
	}
	~Bullet() {

	}

	void onUpdate() {
		if (bulletEndLife < Time::getInstance().getCurrentTime())
		{
			shouldDelete = true;
			return;
		
		}

		glm::vec3 currPos = *transform.getPos();
		glm::vec3 nextPos = currPos + (dir * bulletSpeed * (float)Time::getInstance().getDeltaTime());

		transform.setPos(nextPos);
	}
	bool shouldDelete = false;

protected:
private:
	glm::vec3 dir;
	TransformComponent& transform;
	float bulletSpeed = 100.0f;
	

	double bulletEndLife;
	float bulletLife = 2.0f;
};