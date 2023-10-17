#pragma once

#include <cmath>
#include <iostream>
#include <glm/detail/type_vec.hpp>
#include <glm/detail/type_mat.hpp>
#include <glm/glm.hpp>

#define PI 3.14159265358979323846

struct Quaternion {
    double x, y, z, w;
};

// This assumes the axis magnitude is 1
Quaternion axisAngleToQuaternion(double angle, double axisX, double axisY, double axisZ) {
    Quaternion q;
    float halfAngle = angle / 2.0f;
    float sinHalfAngle = sin(halfAngle);
    q.w = cos(halfAngle);
    q.x = axisX * sinHalfAngle;
    q.y = axisY * sinHalfAngle;
    q.z = axisZ * sinHalfAngle;
    return q;
}

glm::vec3 quaternionToAxisAxis(Quaternion& quat) {
    float angle_rad = acos(quat.w) * 2;

    float x = quat.x / sin(angle_rad / 2);
    float y = quat.y / sin(angle_rad / 2);
    float z = quat.z / sin(angle_rad / 2);
    
    return glm::vec3(x, y, z);
}

