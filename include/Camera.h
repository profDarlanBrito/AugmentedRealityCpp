#ifndef CAMERA_H
#define CAMERA_H

#include "GLMath.h"

class Camera
{
private:
	glm::vec3 mEye;          // Posição da câmera
	glm::vec3 mViewDirection; // Direção de visão da câmera
	glm::vec3 mUpDirection;   // Direção "para cima" da câmera
	// Adicione os campos para yaw e pitch
	float mYaw = -90.0f;      // Yaw inicial (olhando para -Z)
	float mPitch = 0.0f;      // Pitch inicial
	float mRoll = 0.0f;       // Roll inicial (opcional, geralmente não usado em câmeras 3D)
	glm::vec3 mFront = glm::vec3(0.0f, 0.0f, -1.0f); // Adicionado para uso em processMouseMovement
	glm::vec3 mRight = glm::vec3(1.0f, 0.0f, 0.0f);  // Opcional, usado em processMouseMovement
	glm::vec3 mWorldUp = glm::vec3(0.0f, 1.0f, 0.0f); // Opcional, usado em processMouseMovement


public:
	float mFov = 45.0f; // Campo de visão (FOV) da câmera
	float mNear = 0.1f; // Plano de recorte próximo
	float mFar = 100.0f; // Plano de recorte distante	
	float mAspectRatio = 16.0f / 9.0f; // Proporção da tela (pode ser ajustada conforme necessário)
	// Método para obter a matriz de visualização da câmera

	/**
	* @brief Generates the view matrix for the camera.
	* @see https://www.youtube.com/watch?v=cFHX5gSMjTs&list=PLvv0ScY6vfd9zlZkIIqGDeG5TUWswkMox&index=31 youtube video explaining how to implement the getViewMatrix function in a camera class
	* @return The view matrix as a glm::mat4.
	*/
	glm::mat4 getViewMatrix() const
	{
		// The second parameter of glm::lookAt should be the point the camera is looking at (target), not the direction.
		// So we need to add the view direction to the camera position.
		return glm::lookAt(mEye, mEye + mViewDirection, mUpDirection);
	}

	/**
	* @brief Default constructor for the Camera class.
	*/
	Camera() : mEye(0.0f, 0.0f, 0.0f), mViewDirection(0.0f, 0.0f, -1.0f), mUpDirection(0.0f, 1.0f, 0.0f) {}

	/**
	* @brief Constructor for the Camera class with specified parameters.
	*/
	Camera(const glm::vec3& eye, const glm::vec3& viewDirection, const glm::vec3& upDirection) {
		mEye = eye;
		mViewDirection = glm::normalize(viewDirection);
		mUpDirection = glm::normalize(upDirection);
	}
	/**
	* @brief Sets the position of the camera.
	*/
	void setPosition(const glm::vec3& eye) {
		mEye = eye;
	}
	/**
	* @brief Sets the view direction of the camera.
	*/
	void setViewDirection(const glm::vec3& viewDirection) {
		mViewDirection = glm::normalize(viewDirection);
	}

	/**
	* @brief Sets the up direction of the camera.
	* @note The up direction should be normalized to ensure correct camera orientation. The up direction is typically a vector pointing upwards in the world space, such as (0, 1, 0).
	*/
	void setUpDirection(const glm::vec3& upDirection) {
		mUpDirection = glm::normalize(upDirection);
	}
    glm::mat4 getViewMatrix(){
        return glm::lookAt(mEye, mViewDirection, mUpDirection);
	}

	void MoveForward(float distance)
	{
		mEye += mViewDirection * distance;
	}
	void MoveBackward(float distance)
	{
		mEye -= mViewDirection * distance;
	}
	void MoveLeft(float distance)
	{
		glm::vec3 left = glm::normalize(glm::cross(mViewDirection, mUpDirection));
		mEye -= left * distance;
	}
	void MoveRight(float distance)
	{
		glm::vec3 right = glm::normalize(glm::cross(mUpDirection, mViewDirection));
		mEye += right * distance;
	}
	void processMouseMovement(float xoffset, float yoffset);
};
#endif // !CAMERA_HPP
