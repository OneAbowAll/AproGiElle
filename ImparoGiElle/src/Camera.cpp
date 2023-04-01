#include "Camera.h"

Camera::Camera(glm::vec3 position = glm::vec3(0))
    :m_View(glm::translate(glm::mat4(1.0f), position)), m_Proj(glm::perspective(45.0f, 16.0f / 9.0f, 0.1f, 100.0f)),
    m_Position(position), m_PitchYawRoll(0.0f), m_Forward(1.0f, 0, 0), m_Up(0, 1.0f, 0), m_Right(0, 0, 1.0f)
{
}

Camera::~Camera()
{
}

void Camera::Move(glm::vec3 amount)
{
    m_Position += amount;
}

void Camera::SetPosition(glm::vec3 newPosition)
{
    m_Position = newPosition;
}

void Camera::Rotate(glm::vec3 amount)
{
    m_PitchYawRoll += amount;

    glm::vec3 direction = glm::vec3(
        cos(glm::radians(m_PitchYawRoll.y)) * cos(glm::radians(m_PitchYawRoll.x)),
        sin(glm::radians(m_PitchYawRoll.x)),
        sin(glm::radians(m_PitchYawRoll.y)) * cos(glm::radians(m_PitchYawRoll.x))
    );
    m_Forward = glm::normalize(direction);
    m_Right = glm::normalize(glm::cross(m_Forward, glm::vec3(0.0f, 1.0f, 0.0f)));
    m_Up = glm::cross(m_Right, m_Forward);
}

void Camera::SetRotation(glm::vec3 pitchYawRoll)
{
    m_PitchYawRoll = pitchYawRoll;
}

void Camera::CalculateView()
{
    m_View = glm::lookAt(m_Position, m_Position + m_Forward, m_Up);
}
