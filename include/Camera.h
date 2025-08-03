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
	glm::vec3 mFront = glm::vec3(0.0f, 0.0f, -1.0f); // Adicionado para uso em processMouseMovement
	glm::vec3 mRight = glm::vec3(1.0f, 0.0f, 0.0f);  // Opcional, usado em processMouseMovement
	glm::vec3 mWorldUp = glm::vec3(0.0f, 1.0f, 0.0f); // Opcional, usado em processMouseMovement
	glm::vec3 mUp = glm::vec3(0.0f, 1.0f, 0.0f); // Direção "para cima" da câmera


public:
	float mFov = 45.0f; // Campo de visão (FOV) da câmera
	float mNear = 0.1f; // Plano de recorte próximo
	float mFar = 100.0f; // Plano de recorte distante	
	float mAspectRatio = 16.0f / 9.0f; // Proporção da tela (pode ser ajustada conforme necessário)
	// Método para obter a matriz de visualização da câmera

	glm::mat4 getViewMatrix() const
	{
		// O segundo parâmetro de glm::lookAt deve ser o ponto para onde a câmera está olhando (target), não a direção.
 		// Portanto, precisamos somar a direção de visão à posição da câmera.
		return glm::lookAt(mEye, mEye + mViewDirection, mUpDirection);
	}
	Camera() : mEye(0.0f, 0.0f, 0.0f), mViewDirection(0.0f, 0.0f, -1.0f), mUpDirection(0.0f, 1.0f, 0.0f) {}
	Camera(const glm::vec3& eye, const glm::vec3& viewDirection, const glm::vec3& upDirection) {
		mEye = eye;
		mViewDirection = glm::normalize(viewDirection);
		mUpDirection = glm::normalize(upDirection);
	}
	void setPosition(const glm::vec3& eye) {
		mEye = eye;
	}
	void setViewDirection(const glm::vec3& viewDirection) {
		mViewDirection = glm::normalize(viewDirection);
	}
	void setUpDirection(const glm::vec3& upDirection) {
		mUpDirection = glm::normalize(upDirection);
	}
    glm::mat4 getViewMatrix(){
        return glm::lookAt(mEye, mViewDirection, mUp);
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
