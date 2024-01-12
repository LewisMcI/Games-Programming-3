#pragma once
#include <corecrt_math.h>
#include <glm/glm.hpp>

class Quaternion {
    double w; // Real Part
    double x; // I Component
    double y; // J Component
    double z; // K Component
    Quaternion() {
        w = 0; x = 0; y = 0; z = 0;
    }
    Quaternion(double w, double x, double y, double z) {
        this->w = w;
        this->x = x;
        this->y = y;
        this->z = z;
    }

    static Quaternion& MultiplyQuaternions(Quaternion& quat1, Quaternion& quat2) {
        Quaternion multipliedQuat;
        multipliedQuat.w = quat1.w * quat2.w - quat1.x * quat2.x - quat1.y * quat2.y - quat1.z * quat2.z;
        multipliedQuat.x = quat1.w * quat2.x + quat1.x * quat2.w + quat1.y * quat2.z - quat1.z * quat2.y;
        multipliedQuat.y = quat1.w * quat2.y - quat1.x * quat2.z + quat1.y * quat2.w + quat1.z * quat2.x;
        multipliedQuat.z = quat1.w * quat2.z + quat1.x * quat2.y - quat1.y * quat2.x + quat1.z * quat2.w;
        return multipliedQuat;
    }

    static Quaternion& RotateVectorByQuaternion(glm::vec3 vector, Quaternion& quat) {
        Quaternion& p = Quaternion(0.0f, vector.x, vector.y, vector.z);

        Quaternion& rotatedP = MultiplyQuaternions(quat, p);
        rotatedP.conjugate();

        glm::vec3 rotatedVector = glm::vec3(rotatedP.x, rotatedP.y, rotatedP.z);
    }

    void conjugate() {
        x = -x;
        y = -y;
        z = -z;
    }
    
    void normalize() {
        int magnitude = sqrt(w * w + x * x + y * y + z * z);
        w = w / magnitude;
        x = x / magnitude;
        y = y / magnitude;
        z = z / magnitude;
    }

    glm::mat3 toRotationMatrix() {
        glm::mat3 rotationMatrix = glm::mat3(
            1 - 2 * y * y - 2 * z * z, 2 * x * y - 2 * w * z, 2 * x * z + 2 * w * y,
            2 * x * y + 2 * w * z, 1 - 2 * x * x - 2 * z * z, 2 * y * z - 2 * w * x,
            2 * x * z - 2 * w * y, 2 * y * z + 2 * w * x, 1 - 2 * x * x - 2 * y * y
        );

        return rotationMatrix;
    }
};

