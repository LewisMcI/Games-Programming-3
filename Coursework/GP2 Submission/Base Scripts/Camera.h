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
	
	void setPos(glm::vec3& newPos) {
		this->cameraPos = newPos;
	}

	void followRot(TransformComponent& targetTransform, float distance) {
		// Get the target's position and forward direction
		glm::vec3 targetPos = *(targetTransform.getPos());
		glm::vec3 targetForward = glm::normalize(targetTransform.getModel() * glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));

		// Set the desired offset from the target
		glm::vec3 offset = -targetForward * distance;

		// Set the camera's position and make it look at the target
		setPos(targetPos + offset);
		LookAt(targetPos);
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