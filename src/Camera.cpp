#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm> // Para std::clamp

// Substitua std::clamp por uma função utilitária local para compatibilidade com C++ versões anteriores a C++17
template <typename T>
T clamp(T value, T minVal, T maxVal) {
    return std::max(minVal, std::min(value, maxVal));
}

void Camera::processMouseMovement(float xoffset, float yoffset)
{
    float sensitivity = 1.0f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    mYaw   += xoffset;
    mPitch += yoffset;

    // Use a função clamp local
    mPitch = clamp(mPitch, -89.0f, 89.0f);

    glm::vec3 front;
    front.x = cos(glm::radians(mYaw)) * cos(glm::radians(mPitch));
    front.y = sin(glm::radians(mPitch));
    front.z = sin(glm::radians(mYaw)) * cos(glm::radians(mPitch));
    mFront = glm::normalize(front);

    mRight = glm::normalize(glm::cross(mFront, mWorldUp));
    mUp    = glm::normalize(glm::cross(mRight, mFront));
}


