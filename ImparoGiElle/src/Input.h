#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"

class Input
{
private:
	GLFWwindow* m_Window;

public:
	Input(GLFWwindow* window);

	glm::vec2 MouseDelta();
	glm::vec3 MovementDirection();
	bool ButtonPressed(int key);
	bool MouseButtonPressed(int button);

};