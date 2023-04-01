#include "Input.h"

Input::Input(GLFWwindow* window)
	:m_Window(window)
{
}

glm::vec2 Input::MouseDelta()
{
	static glm::vec2 oldMousePos(0.0f, 0.0f);

	double xpos, ypos;
	glfwGetCursorPos(m_Window, &xpos, &ypos);

	glm::vec2 mousePosition = glm::vec2(xpos, ypos);
	glm::vec2 mouseDelta = mousePosition - oldMousePos;

	oldMousePos = mousePosition;


	return mouseDelta;
}

//Metodo molto specifico per la situazione attuale
glm::vec3 Input::MovementDirection()
{
	glm::vec3 direction(
		(ButtonPressed(GLFW_KEY_W)) ? 1.0f : ((ButtonPressed(GLFW_KEY_S)) ? -1.0f : 0.0f),
		(ButtonPressed(GLFW_KEY_SPACE)) ? 1.0f : ((ButtonPressed(GLFW_KEY_LEFT_CONTROL)) ? -1.0f : 0.0f),
		(ButtonPressed(GLFW_KEY_D)) ? 1.0f : ((ButtonPressed(GLFW_KEY_A)) ? -1.0f : 0.0f)
	);

	return (direction);
}

bool Input::ButtonPressed(int key)
{
	return (glfwGetKey(m_Window, key) == GLFW_PRESS);
}

bool Input::MouseButtonPressed(int button)
{
	return (glfwGetMouseButton(m_Window, 1) == GLFW_PRESS);
}
