#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <iostream>
#include "Component.h"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include "../Base Scripts/Camera.h"

#define PI 3.141592

struct TransformComponent : public Component
{
public:
	TransformComponent(const glm::vec3& pos = glm::vec3(), const glm::quat& rot = glm::quat(1.0f, 0.0f, 0.0f, 0.0f), const
		glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f))
	{
		this->pos = pos;
		this->rot = rot;
		this->scale = scale;
	}

	inline glm::mat4 getModel() const //runs as compile time
	{
		glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), pos);
		glm::mat4 rotationMatrix = glm::mat4_cast(rot);
		glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), scale);

		return translationMatrix * rotationMatrix * scaleMatrix;
	}
	inline const glm::vec3* getPos() const { return &pos; } //getters
	inline const glm::quat* getRot() const { return &rot; }
	inline const glm::vec3* getScale() const { return &scale; }
	inline void setPos(const glm::vec3& pos) { this->pos = pos; } // setters
	inline void setRot(const glm::quat& rot) { this->rot = rot; }
	inline void setScale(const glm::vec3& scale) { this->scale = scale; }


	// Get the transformed "up" vector
	glm::vec3 getUp() const {
		// Assuming 'rotation' is a quaternion
		glm::mat4 rotationMatrix = glm::mat4_cast(rot);
		glm::vec3 upVector = glm::vec3(0.0f, 1.0f, 0.0f);

		// Rotate the up vector using the rotation matrix
		glm::vec3 rotatedUpVector = glm::mat3(rotationMatrix) * upVector;

		return glm::normalize(rotatedUpVector);
	}
	
	glm::vec3 getRight() const {
		glm::vec3 fixedRightVector = glm::vec3(1.0f, 0.0f, 0.0f);
		return glm::normalize(rot * fixedRightVector);
	}

	void followCamera(Camera* camera) {
		glm::vec3 pos = camera->getPos();
		setPos(pos);
		glm::vec3 forward = camera->getForward();
		glm::vec3 up = camera->getUp();
		glm::vec3 right = glm::cross(up, forward);
		
		// Extract the rotation angles (in radians) from the rotation matrix
		// Calculate pitch (rotation around x-axis)
		float pitch = std::asin(-forward.y);

		// Calculate yaw (rotation around y-axis)
		float yaw = std::atan2(forward.x, forward.z);

		// Calculate roll (rotation around z-axis)
		float roll = std::atan2(up.x, up.y);

		glm::quat newQuat = glm::vec3(pitch, yaw, roll);
		setRot(newQuat);
	}

	void followCamera(Camera* camera, float distance) {
		// Get the camera position and forward direction
		glm::vec3 cameraPos = camera->getPos();
		glm::vec3 cameraForward = camera->getForward();

		// Calculate the new position relative to the camera's forward direction
		glm::vec3 newPos = cameraPos + distance * cameraForward;

		// Set the new position
		setPos(newPos);

		// Calculate the rotation to face the camera
		glm::quat newQuat = quatLookAt(glm::normalize(cameraPos - newPos), camera->getUp());

		// Set the new rotation
		setRot(newQuat);
	}
	glm::quat quatLookAt(const glm::vec3& direction, const glm::vec3& up) {
		glm::mat3 rotationMatrix;

		// Create a rotation matrix using the LookAt direction and up vector
		rotationMatrix[2] = -glm::normalize(direction); // Negate the direction because GLM uses a right-handed coordinate system
		rotationMatrix[0] = glm::normalize(glm::cross(up, rotationMatrix[2]));
		rotationMatrix[1] = glm::cross(rotationMatrix[2], rotationMatrix[0]);

		// Convert the rotation matrix to a quaternion
		glm::quat rotationQuat(rotationMatrix);

		return rotationQuat;
	}

	glm::vec3 rotateVector(const glm::vec3& axis, float angle, const glm::vec3& vectorToRotate) {
		// Create a rotation matrix
		glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, axis);

		// Transform the vector using the rotation matrix
		glm::vec4 rotatedVector = rotationMatrix * glm::vec4(vectorToRotate, 1.0f);

		// Return the rotated vector
		return glm::vec3(rotatedVector);
	}

	void move(const glm::vec3 value){
		pos += value;
	}

	// Takes angles in degrees
	void rotate(float angleDegrees, const glm::vec3& axis) {
		glm::quat rotationDelta = glm::angleAxis(glm::radians(angleDegrees), axis);
		rot = rot * rotationDelta;
	}

protected:
private:
	glm::vec3 pos;
	glm::quat rot;
	glm::vec3 scale;
};