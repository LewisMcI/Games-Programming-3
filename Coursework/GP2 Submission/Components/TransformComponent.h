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


	glm::vec3 getUp() {
		glm::mat4 rotX = glm::rotate(rot.x, glm::vec3(1.0, 0.0, 0.0));
		glm::mat4 rotY = glm::rotate(rot.y, glm::vec3(0.0, 1.0, 0.0));
		glm::mat4 rotZ = glm::rotate(rot.z, glm::vec3(0.0, 0.0, 1.0));
		glm::mat4 rotMat = rotX * rotY * rotZ;

		return glm::vec3(rotMat[1][0], rotMat[1][1], rotMat[1][2]);
	}

	glm::vec3 getRight() {
		glm::mat4 rotX = glm::rotate(rot.x, glm::vec3(1.0, 0.0, 0.0));
		glm::mat4 rotY = glm::rotate(rot.y, glm::vec3(0.0, 1.0, 0.0));
		glm::mat4 rotZ = glm::rotate(rot.z, glm::vec3(0.0, 0.0, 1.0));
		glm::mat4 rotMat = rotX * rotY * rotZ;

		return glm::vec3(-rotMat[0][0], rotMat[0][1], rotMat[0][2]);
	}

	void move(glm::vec3 value){
		pos += value;
	}

	// Takes angle in radians
	void rotate(glm::vec3 value) {
		rot += value;
	}

protected:
private:
	glm::vec3 pos;
	glm::vec3 rot;
	glm::vec3 scale;
};