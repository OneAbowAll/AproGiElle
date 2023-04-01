#pragma once

#include "Test.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"

#include "Renderer.h"
#include "Camera.h"
#include "Input.h"

namespace test {
	class TestMesh : public Test
	{
	public:
		TestMesh();
		~TestMesh();

		void OnUpdate(GLFWwindow* window, float deltaTime);
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		Camera m_Camera;

		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VBO;
		std::unique_ptr<IndexBuffer> m_IBO;
		std::unique_ptr<Shader> m_Shader;
	};
}