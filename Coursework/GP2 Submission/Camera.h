#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "Components/TransformComponent.h"

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

	void MoveX(float moveAmount)
	{
		cameraPos += forward * moveAmount;
	}

	void MoveZ(float moveAmount)
	{
		glm::vec3 right = glm::normalize(glm::cross(up, forward));
		cameraPos += right * moveAmount;
	}

	void MoveY(float moveAmount)
	{
		cameraPos += up * moveAmount;
	}

	void RotateX(float angle)
	{
		glm::mat4 rotation = glm::rotate(angle, up);

		forward = glm::vec3(glm::normalize(rotation * glm::vec4(forward, 0.0)));
	}

	void RotateY(float angle)
	{
		glm::vec3 right = glm::normalize(glm::cross(up, forward));

		forward = glm::vec3(glm::normalize(glm::rotate(angle, right) * glm::vec4(forward, 0.0)));
	}


protected:
private:
	glm::mat4 projection;
	glm::vec3 cameraPos;
	glm::vec3 forward;
	glm::vec3 up;
};