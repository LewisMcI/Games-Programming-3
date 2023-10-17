#pragma once

#include <cmath>
#include <iostream>
#include <glm/detail/type_vec.hpp>
#include <glm/detail/type_mat.hpp>
#include <glm/glm.hpp>

class Quaternion {
public:

    // Rotate with Vector3





    float getMagnitude() {

    }

    void normalize(){
        float mag = getMagnitude();
        if (mag > 0) {
            w /= mag;
            x /= mag;
            y /= mag;
            z /= mag;
        }
    }

    glm::mat4 toMatrix() const {
        glm::mat4 rotationMatrix = glm::mat4(1.0f);

        float xx = x * x;
        float xy = x * y;
        float xz = x * z;
        float xw = x * w;
        float yy = y * y;
        float yz = y * z;
        float yw = y * w;
        float zz = z * z;
        float zw = z * w;

        rotationMatrix[0][0] = 1 - 2 * (yy + zz);
        rotationMatrix[0][1] = 2 * (xy - zw);
        rotationMatrix[0][2] = 2 * (xz + yw);

        rotationMatrix[1][0] = 2 * (xy + zw);
        rotationMatrix[1][1] = 1 - 2 * (xx + zz);
        rotationMatrix[1][2] = 2 * (yz - xw);

        rotationMatrix[2][0] = 2 * (xz - yw);
        rotationMatrix[2][1] = 2 * (yz + xw);
        rotationMatrix[2][2] = 1 - 2 * (xx + yy);

        return rotationMatrix;
    }
    // Member variables
    float w, x, y, z;
    float mag;
};

