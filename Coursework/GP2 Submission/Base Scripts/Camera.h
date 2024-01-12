#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

struct Camera
{
public:
	Camera(const glm::vec3& pos, float fov, float aspect, float nearClip, float farClip)
		: cameraPos(pos), forward(0.0f, 0.0f, 1.0f), up(0.0f, 1.0f, 0.0f),
		projection(glm::perspective(fov, aspect, nearClip, farClip)) {}

	const glm::vec3 getPos() const{
		return cameraPos;
	}

	const glm::vec3 getForward() const {
		return forward;
	}

	const glm::vec3 getUp() const {
		return up;
	}

	const glm::vec3 getRight() const {
		return glm::normalize(glm::cross(forward, up));
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
		return projection * getView();
	}

	void MoveForward(float amt)
	{
		cameraPos += forward * amt;
	}

	void MoveLeft(float amt)
	{
		cameraPos += glm::cross(up, forward) * amt;
	}

	void RotateX(float angle)
	{
		glm::mat4 rotation = glm::rotate(angle, up);

		forward = glm::normalize(glm::vec3(rotation * glm::vec4(forward, 0.0)));
	}

	void RotateY(float angle)
	{
		glm::vec3 right = glm::normalize(glm::cross(up, forward));

		forward = glm::normalize(glm::vec3(glm::rotate(angle, right) * glm::vec4(forward, 0.0)));
	}

protected:
private:
	glm::mat4 projection;
	glm::vec3 cameraPos;
	glm::vec3 forward;
	glm::vec3 up;
};