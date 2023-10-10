#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class Quaternion {
public:
    // Constructors
    Quaternion() : quat(1.0f, 0.0f, 0.0f, 0.0f) {}
    Quaternion(float w, float x, float y, float z) : quat(w, x, y, z) {}
    Quaternion(glm::quat newQuat) : quat(quat.w, quat.x, quat.y, quat.z) {}

    // Set the quaternion values
    void Set(float w, float x, float y, float z) {
        quat = glm::quat(w, x, y, z);
    }

    // Normalize the quaternion
    void Normalize() {
        quat = glm::normalize(quat);
    }

    // Quaternion multiplication
    Quaternion operator*(const Quaternion& other) const {
        return Quaternion(glm::cross(quat, other.quat));
    }

    // Convert the quaternion to a rotation matrix
    glm::mat4 ToRotationMatrix() const {
        return glm::mat4_cast(quat);
    }

    // Get the underlying glm::quat
    glm::quat GetQuaternion() const {
        return quat;
    }

private:
    glm::quat quat;
};
