#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>

struct Camera {
public:
    Camera() {}

    void initCamera(const glm::vec3& pos, float fov, float aspect, float nearClip, float farClip) {
        this->cameraPos = pos;
        this->orientation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f); // Initialize with no rotation
        this->projection = glm::perspective(fov, aspect, nearClip, farClip);
    }

    glm::vec3 getPos() {
        return this->cameraPos;
    }

    inline glm::mat4 getProjection() const {
        return projection;
    }

    inline glm::mat4 getView() const {
        glm::mat4 rotationMatrix = glm::mat4_cast(orientation);
        glm::vec3 forward = glm::vec3(rotationMatrix * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f));
        glm::vec3 up = glm::vec3(rotationMatrix * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));
        return glm::lookAt(cameraPos, cameraPos + forward, up);
    }

    inline glm::mat4 GetViewProjection() const {
        return projection * getView();
    }

    void LookAt(glm::vec3 target) {
        glm::vec3 dir = target - cameraPos;
        glm::vec3 forward = glm::normalize(dir);

        // Calculate the new orientation as a quaternion
        orientation = glm::quat(glm::lookAt(glm::vec3(0.0f), forward, glm::vec3(0.0f, 1.0f, 0.0f)));
    }

    void MoveX(float moveAmount) {
        glm::vec3 forward = glm::vec3(orientation * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f));
        cameraPos += forward * moveAmount;
    }

    void MoveZ(float moveAmount) {
        glm::vec3 forward = glm::vec3(orientation * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f));
        glm::vec3 right = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), forward));
        cameraPos += right * moveAmount;
    }

    void MoveY(float moveAmount) {
        glm::vec3 up = glm::vec3(orientation * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));
        cameraPos += up * moveAmount;
    }

    void RotateX(float angle) {
        glm::quat rotation = glm::angleAxis(angle, glm::vec3(0.0f, 1.0f, 0.0f)); // Invert angle here
        orientation = rotation * orientation;
        orientation = glm::normalize(orientation); // Normalize to maintain unit quaternion
    }

    void RotateY(float angle) {
        glm::quat rotation = glm::angleAxis(-angle, glm::vec3(1.0f, 0.0f, 0.0f)); // Invert angle here
        orientation = orientation * rotation;
        orientation = glm::normalize(orientation); // Normalize to maintain unit quaternion
    }

protected:
private:
    glm::mat4 projection;
    glm::vec3 cameraPos;
    glm::quat orientation; // Quaternion to represent camera orientation
};
