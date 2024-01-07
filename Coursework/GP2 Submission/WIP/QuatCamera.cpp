#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Camera
{
public:
    Camera() {}

    void initCamera(const glm::vec3& pos, float fov, float aspectRatio, float near, float far)
    {
        this->fov = fov;
        this->aspectRatio = aspectRatio;
        this->near = near;
        this->far = far;

        position = pos;
        orientation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f); // Identity quaternion
        updateProjectionMatrix();
    }

    glm::vec3 getPos()
    {
        return this->position;
    }

    glm::mat4 getProjection() const
    {
        return projectionMatrix;
    }

    glm::mat4 getView() const
    {
        return glm::translate(glm::mat4_cast(orientation), -position);
    }

    glm::mat4 GetViewProjection() const
    {
        return getProjection() * glm::mat4_cast(orientation) * glm::translate(glm::mat4(1.0f), -position);
    }

    void LookAt(const glm::vec3& target)
    {
        glm::vec3 forward = glm::normalize(target - position);
        glm::vec3 right = glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), forward);
        glm::vec3 up = glm::cross(forward, right);

        orientation = glm::quat_cast(glm::mat3(right, up, -forward));
    }

    void MoveZ(float distance)
    {
        glm::vec3 movement = orientation * glm::vec3(-distance, 0.0f, 0.0f);
        position += movement;
    }

    void MoveY(float distance)
    {
        glm::vec3 movement = orientation * glm::vec3(0.0f, distance, 0.0f);
        position += movement;
    }

    void MoveX(float distance)
    {
        glm::vec3 movement = orientation * glm::vec3(0.0f, 0.0f, -distance);
        position += movement;
    }

    // Rotate the camera around the local Y-axis (yaw)
    void RotateY(float angle) {
        // Calculate the new orientation quaternion for yaw
        glm::quat yawRotation = glm::angleAxis(-angle, glm::vec3(0.0f, 1.0f, 0.0f));
        orientation = orientation * yawRotation;
        orientation = glm::normalize(orientation); // Normalize the orientation
    }

    // Rotate the camera around the local X-axis (pitch)
    void RotateX(float angle) {
        // Calculate the new orientation quaternion for pitch
        glm::quat pitchRotation = glm::angleAxis(angle, glm::vec3(1.0f, 0.0f, 0.0f));
        orientation = pitchRotation * orientation;
        orientation = glm::normalize(orientation); // Normalize the orientation
    }


private:
    glm::vec3 position;
    glm::quat orientation;
    float fov;
    float aspectRatio;
    float near;
    float far;
    glm::mat4 projectionMatrix;

    void updateProjectionMatrix()
    {
        projectionMatrix = glm::perspective(fov, aspectRatio, near, far);
    }
};
