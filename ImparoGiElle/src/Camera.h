#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Camera
{
public:
	Camera(glm::vec3 position);
	~Camera();

	void Move(glm::vec3 amount);
	void SetPosition(glm::vec3 newPosition);

	void Rotate(glm::vec3 amount);
	void SetRotation(glm::vec3 pitchYawRoll);

	void CalculateView();

	inline const glm::vec3 Up() const { return m_Up; }
	inline const glm::vec3 Forward() const { return m_Forward; }
	inline const glm::vec3 Right() const { return m_Right; }

	inline const glm::vec3 Position() const { return m_Position; }
	inline const glm::vec3 Rotation() const { return m_PitchYawRoll; }

	inline const glm::mat4 Proj() const { return m_Proj; }
	inline const glm::mat4 View() const { return m_View; }

private:
	glm::vec3 m_Position;

	glm::vec3 m_Up;
	glm::vec3 m_Forward;
	glm::vec3 m_Right;

	glm::vec3 m_PitchYawRoll;

	glm::mat4 m_Proj, m_View;
};