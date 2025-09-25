#include "Camera.h"


// Change std::clamp by an utility function for compatibility with C++ versions prior to C++17
template <typename T>
T clamp(T value, T minVal, T maxVal) {
    return std::max(minVal, std::min(value, maxVal));
}

/**
* @brief Process mouse movement to update camera orientation.
* @param xoffset The change in the x direction (horizontal movement).
* @param yoffset The change in the y direction (vertical movement).
* @note This function adjusts the camera's yaw and pitch based on mouse movement. It applies a sensitivity factor to the offsets and clamps the pitch to prevent flipping the camera upside down. The front, right, and up vectors of the camera are recalculated based on the new yaw and pitch angles.
* * @see https://www.khronos.org/opengl/wiki/Camera
* * @see https://www.khronos.org/opengl/wiki/Mouse_Motion
* * @see https://www.khronos.org/opengl/wiki/Camera_Movement
* * @see https://www.khronos.org/opengl/wiki/Camera_Orientation
* * @see https://www.khronos.org/opengl/wiki/Camera_Yaw_Pitch_Roll
* * @see https://youtu.be/Q8aQ1t70k-s?si=2u06JmAi_L-hnHs0 youtube video explaining how to implement function to process mouse movement in a camera class
* * @note This function is typically called in response to mouse movement events, such as when the user drags the mouse while holding down a button.
* * @note This function is part of the Camera class, which manages the camera's position and orientation in the 3D scene.
* * @see https://www.khronos.org/opengl/wiki/Camera#Mouse_Movement
*/
void Camera::processMouseMovement(float xoffset, float yoffset)
{
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    mYaw   -= xoffset;
    mPitch += yoffset;

    // Use a função clamp local
    mPitch = clamp(mPitch, -180.0f, 180.0f);

    glm::vec3 front;
    front.x = cos(glm::radians(mYaw)) * cos(glm::radians(mPitch));
    front.y = sin(glm::radians(mPitch));
    front.z = sin(glm::radians(mYaw)) * cos(glm::radians(mPitch));
    mFront = glm::normalize(front);
	//mFront = glm::normalize(glm::vec3(0.0f) - front);
	mViewDirection = mFront;
	mEye = mFront * mRadius; // Atualiza a posição da câmera com base no raio

    mRight = glm::normalize(glm::cross(mFront, mWorldUp));
    //mUpDirection = glm::normalize(glm::vec3(glm::rotate(glm::mat4(1.0f), glm::radians(mRoll), mFront) * glm::vec4(mWorldUp, 0.0f)));
	//std::cout << "Camera::processMouseMovement: mYaw: " << mYaw << ", mPitch: " << mPitch << ", mRoll: " << mRoll << std::endl;
}

/**
    * @brief Atualiza os vetores de direção e para cima da câmera a partir dos ângulos de roll, pitch e yaw.
    * @param yaw Ângulo de rotação em torno do eixo Y (em graus).
    * @param pitch Ângulo de rotação em torno do eixo X (em graus).
    * @param roll Ângulo de rotação em torno do eixo Z (em graus).
    */
void Camera::updateDirectionFromAngles(float yaw, float pitch, float roll) {
    mYaw = yaw;
    mPitch = pitch;
    mRoll = roll;

    // Calcula o vetor frente (direção)
    glm::vec3 front;
    front.x = cos(glm::radians(mYaw)) * cos(glm::radians(mPitch));
    front.y = sin(glm::radians(mPitch));
    front.z = sin(glm::radians(mYaw)) * cos(glm::radians(mPitch));
    mFront = glm::normalize(front);
    mViewDirection = mFront;

    // Calcula o vetor direita
    mRight = glm::normalize(glm::cross(mFront, mWorldUp));

    // Calcula o vetor para cima com roll
    glm::mat4 rollMat = glm::rotate(glm::mat4(1.0f), glm::radians(mRoll), mFront);
    mUpDirection = glm::normalize(glm::vec3(rollMat * glm::vec4(mWorldUp, 0.0f)));
}
