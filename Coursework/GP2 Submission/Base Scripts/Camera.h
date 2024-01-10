#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "../Components/TransformComponent.h"

struct Camera
{
public:
	Camera() {}

	void initCamera(const glm::vec3& pos, float fov, float aspect, float nearClip, float farClip)
	{
		this->cameraPos = pos;
		this->forward = glm::vec3(0.0f, 0.0f, 1.0f);
		this->up = glm::vec3(0.0f, 1.0f, 0.0f);
		this->projection = glm::perspective(fov, aspect, nearClip, farClip);
	}

	glm::vec3 getPos()
	{
		return this->cameraPos;
	}

	glm::vec3 getForward() {
		return this->forward;
	}

	glm::vec3 getUp() {
		return up;
	}

	glm::vec3 getRight() {
		return glm::cross(forward, up);
	}

	void setPos(glm::vec3& newPos) {
		this->cameraPos = newPos;
	}
	void setRot(glm::vec3& newRot) {
		// Create a rotation matrix based on the new rotation angles
		glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), newRot.x, glm::vec3(1.0f, 0.0f, 0.0f))
			* glm::rotate(glm::mat4(1.0f), newRot.y, glm::vec3(0.0f, 1.0f, 0.0f))
			* glm::rotate(glm::mat4(1.0f), newRot.z, glm::vec3(0.0f, 0.0f, 1.0f));

		// Update the forward and up vectors by multiplying them with the rotation matrix
		forward = glm::vec3(rotationMatrix * glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
		up = glm::vec3(rotationMatrix * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));

		// Optionally, you may want to normalize the vectors if needed
		forward = glm::normalize(forward);
		up = glm::normalize(up);
	}

	void lookAtTransform(TransformComponent& targetTransform, float distance) {
		// Get the target's position and forward direction
		glm::vec3 targetPos = *(targetTransform.getPos());
		glm::vec3 targetForward = glm::normalize(targetTransform.getModel() * glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));

		// Set the desired offset from the target
		glm::vec3 offset = -targetForward * distance;

		// Set the camera's position and make it look at the target
		setPos(targetPos + offset);
		LookAt(targetPos);
	}
	void followTransform(TransformComponent& transform) {
		setPos(*transform.getPos());
		setRot(*transform.getRot());
	}

	void MoveForward(float amt)
	{
		cameraPos += forward * amt;
	}

	void MoveLeft(float amt)
	{
		cameraPos += glm::cross(up, forward) * amt;
	}

	inline glm::mat4 getProjection() const
	{
		return projection;
	}

	inline glm::mat4 getView() const
	{
		return glm::lookAt(cameraPos, cameraPos + forward, up);
	}

	inline glm::mat4 GetViewProjection() const
	{
		return projection * glm::lookAt(cameraPos, cameraPos + forward, up);
	}

	void LookAt(glm::vec3 target) {
		glm::vec3 dir = target - cameraPos;
		forward = glm::normalize(dir);
	}
protected:
private:
	glm::mat4 projection;
	glm::vec3 cameraPos;
	glm::vec3 forward;
	glm::vec3 up;
};