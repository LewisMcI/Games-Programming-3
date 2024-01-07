#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <iostream>
#include "Component.h"

#define PI 3.141592

struct TransformComponent : public Component
{
public:
	TransformComponent(const glm::vec3& pos = glm::vec3(), const glm::vec3& rot = glm::vec3(), const
		glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f))
	{
		this->pos = pos;
		this->rot = rot;
		this->scale = scale;
	}

	inline glm::mat4 getModel() const //runs as compile time
	{
		glm::mat4 posMat = glm::translate(pos);
		glm::mat4 scaleMat = glm::scale(scale);
		glm::mat4 rotX = glm::rotate(rot.x, glm::vec3(1.0, 0.0, 0.0));
		glm::mat4 rotY = glm::rotate(rot.y, glm::vec3(0.0, 1.0, 0.0));
		glm::mat4 rotZ = glm::rotate(rot.z, glm::vec3(0.0, 0.0, 1.0));
		glm::mat4 rotMat = rotX * rotY * rotZ;
		return posMat * rotMat * scaleMat;
	}
	inline glm::vec3* getPos() { return &pos; } //getters
	inline glm::vec3* getRot() { return &rot; }
	inline glm::vec3* getScale() { return &scale; }
	inline void setPos(glm::vec3& pos) { this->pos = pos; } // setters
	inline void setRot(glm::vec3& rot) { this->rot = rot; }
	inline void setScale(glm::vec3& scale) { this->scale = scale; }

	void moveX(float distance){
		pos.x += distance;
	}

	void moveY(float distance){
		pos.y += distance;
	}

	void moveZ(float distance){
		pos.z += distance;
	}

	float toRadians(float degrees) { return degrees * (PI / 180); }


	// Takes angle in degrees
	void rotateX(float angle) {
		// Convert degrees to radians
		angle = toRadians(angle);
		// Add rotation
		rot.x += angle;
	}

	// Takes angle in degrees
	void rotateY(float angle) {
		// Convert degrees to radians
		angle = toRadians(angle);
		// Add rotation
		rot.y += angle;
	}

	// Takes angle in degrees
	void rotateZ(float angle) {
		// Convert degrees to radians
		angle = toRadians(angle);
		// Add rotation
		rot.z += angle;
	}
protected:
private:
	glm::vec3 pos;
	glm::vec3 rot;
	glm::vec3 scale;
};