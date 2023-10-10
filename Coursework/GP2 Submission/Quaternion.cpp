#include "Quaternion.h" // Include your Quaternion header file

// Constructors
Quaternion::Quaternion() : w(1.0f), x(0.0f), y(0.0f), z(0.0f) {}

Quaternion::Quaternion(float w, float x, float y, float z) : w(w), x(x), y(y), z(z) {}

Quaternion::Quaternion(float angle, const glm::vec3& axis) {
    float halfAngle = angle * 0.5f;
    w = cos(halfAngle);
    x = axis.x * sin(halfAngle);
    y = axis.y * sin(halfAngle);
    z = axis.z * sin(halfAngle);
}

// Quaternion operations
float Quaternion::magnitude() const {
    return sqrt(w * w + x * x + y * y + z * z);
}

void Quaternion::normalize() {
    float mag = magnitude();
    if (mag > 0) {
        w /= mag;
        x /= mag;
        y /= mag;
        z /= mag;
    }
}

Quaternion Quaternion::conjugate() const {
    return Quaternion(w, -x, -y, -z);
}

// Quaternion arithmetic
Quaternion Quaternion::operator*(const Quaternion& other) const {
    return Quaternion(
        w * other.w - x * other.x - y * other.y - z * other.z,
        w * other.x + x * other.w + y * other.z - z * other.y,
        w * other.y - x * other.z + y * other.w + z * other.x,
        w * other.z + x * other.y - y * other.x + z * other.w
    );
}

Quaternion Quaternion::operator*(float scalar) const {
    return Quaternion(w * scalar, x * scalar, y * scalar, z * scalar);
}

// Interpolation
Quaternion Quaternion::slerp(const Quaternion& q1, const Quaternion& q2, float t) {
    // Ensure the quaternions are normalized
    Quaternion a = q1;
    Quaternion b = q2;
    a.normalize();
    b.normalize();

    // Compute the dot product between the quaternions
    float dot = a.w * b.w + a.x * b.x + a.y * b.y + a.z * b.z;

    // Adjust signs if necessary
    if (dot < 0.0f) {
        b = -b;
        dot = -dot;
    }

    // Threshold to avoid division by zero
    const float threshold = 0.9995f;
    if (dot > threshold) {
        // Linear interpolation when quaternions are close
        Quaternion result = a + t * (b - a);
        result.normalize();
        return result;
    }

    // Ensure the dot product is clamped between -1 and 1
    dot = glm::clamp(dot, -1.0f, 1.0f);

    // Compute the angle between the quaternions
    float theta_0 = acos(dot);
    float theta = theta_0 * t;

    // Compute the slerp factors
    float sin_theta = sin(theta);
    float sin_theta_0 = sin(theta_0);

    float s0 = cos(theta) - dot * sin_theta / sin_theta_0;
    float s1 = sin_theta / sin_theta_0;

    // Perform the slerp interpolation
    return Quaternion(s0 * a.w + s1 * b.w,
        s0 * a.x + s1 * b.x,
        s0 * a.y + s1 * b.y,
        s0 * a.z + s1 * b.z);
}

// Conversion to rotation matrix
glm::mat4 Quaternion::toMatrix() const {
    glm::mat4 rotationMatrix = glm::toMat4(glm::quat(w, x, y, z));
    return rotationMatrix;
}

// Rotation
void Quaternion::rotate(float angle, const glm::vec3& axis) {
    Quaternion rotationQuat(angle, axis);
    *this = rotationQuat * (*this);
    normalize();
}

// Debug
void Quaternion::print() const {
    std::cout << "Quaternion(w, x, y, z): (" << w << ", " << x << ", " << y << ", " << z << ")" << std::endl;
}
