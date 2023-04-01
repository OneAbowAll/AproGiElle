#include "TestMesh.h"
#include <vector>

#include "imgui/imgui.h"
#include "Vertex.h"

test::TestMesh::~TestMesh()
{
}

test::TestMesh::TestMesh() : m_Camera(glm::vec3(-4.0f, 1.0f, 1.0f))
{
    std::vector<Vertex> positions = {
        //Front
        {glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f)},
        {glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f)},
        {glm::vec3(0.0f, 1.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f)},
        {glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f)},

        //Back
        {glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f)},
        {glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)},
        {glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)},
        {glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f)},

        //Top
        {glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)},
        {glm::vec3(0.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f)},
        {glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f)},
        {glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)},

        //Bottom
        {glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)},
        {glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)},
        {glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)},
        {glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)},

        //Left
        {glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)},
        {glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)},
        {glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)},
        {glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)},

        //Right
        {glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f)},
        {glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f)},
        {glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f)},
        {glm::vec3(0.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f)},
    };
    
    std::vector<unsigned int> indices = {
        //Front
        0, 1, 2,
        2, 3, 0,

        //Back
        4, 5, 6,
        6, 7, 4,

        //Top
        8, 9, 10,
        10, 11, 8,

        //Bottom
        12, 13, 14,
        14, 15, 12,

        //Left
        16, 17, 18,
        18, 19, 16,

        //Right
        20, 21, 22,
        22, 23, 20
    };

    m_Mesh = std::make_unique<Mesh>(positions, indices);

    m_Shader = std::make_unique<Shader>("res/shaders/Basic.shader");
    m_Shader->Bind();
    m_Shader->SetUniform4f("u_Color", 0.9f, 0.8f, 0.8f, 1.0f);
}

void test::TestMesh::OnUpdate(GLFWwindow* window, float deltaTime)
{
    Input Input(window);
    glm::vec2 mouseDelta = Input.MouseDelta();

    if (Input.MouseButtonPressed(1))
    {
        //Rotazione camera
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        float yawAmount = mouseDelta.x * deltaTime * 10.0f;
        float pitchAmount = -mouseDelta.y * deltaTime * 10.0f;
        m_Camera.Rotate(glm::vec3(pitchAmount, yawAmount, 0));
    }
    else
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    //Movimento
    float speed = 5.0f * deltaTime;
    if (Input.ButtonPressed(GLFW_KEY_LEFT_SHIFT))
        speed *= 2;

    glm::vec3 direction = Input.MovementDirection();
    glm::vec3 relativedirection = direction.x * m_Camera.Forward() + direction.y * glm::vec3(0, 1.0f, 0) + direction.z * m_Camera.Right();
    m_Camera.Move(relativedirection * speed);

    m_Camera.CalculateView();
}

void test::TestMesh::OnRender()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    Renderer renderer;

    m_Shader->Bind();
    {
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f));
        glm::mat4 mvp = m_Camera.Proj() * m_Camera.View() * model;
        m_Shader->SetUniformMat4f("u_MVP", mvp);

        renderer.Draw(*m_Mesh, *m_Shader);
    }
}

void test::TestMesh::OnImGuiRender()
{
    //ImGui::SliderFloat3("Camera Pos", &m_Camera.m_Position.x, -1000, 1000);
}
