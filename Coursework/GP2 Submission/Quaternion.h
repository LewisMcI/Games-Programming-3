#pragma once

#include <cmath>
#include <iostream>
#include <glm/detail/type_vec.hpp>
#include <glm/detail/type_mat.hpp>
#include <glm/glm.hpp>

class Quaternion {
public:
    // Constructors
    Quaternion();
    Quaternion(float w, float x, float y, float z);
    Quaternion(float angle, const glm::vec3& axis);

    // Quaternion operations
    float magnitude() const;
    void normalize();
    Quaternion conjugate() const;

    // Quaternion arithmetic
    Quaternion operator*(const Quaternion& other) const;
    Quaternion operator*(float scalar) const;

    // Interpolation
    static Quaternion slerp(const Quaternion& q1, const Quaternion& q2, float t);

    // Conversion to rotation matrix
    glm::mat4 toMatrix() const;

    // Rotation
    void rotate(float angle, const glm::vec3& axis);

    // Debug
    void print() const;

    // Member variables
    float w, x, y, z;
};

