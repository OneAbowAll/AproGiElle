#include "VertexArray.h"

#include "Renderer.h"
#include "Vertex.h"

VertexArray::VertexArray()
{
    GLCall(glGenVertexArrays(1, &m_RendererID));
}

VertexArray::~VertexArray()
{
    GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::AddBuffer(const VertexBuffer& vb)
{
    Bind();
	vb.Bind();

    //Positions
    GLCall(glEnableVertexAttribArray(0));
    GLCall(glVertexAttribPointer(0, 3, GL_FLOAT,
        GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Position)));

    //Normals
    GLCall(glEnableVertexAttribArray(1));
    GLCall(glVertexAttribPointer(1, 3, GL_FLOAT,
        GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Normal)));
}

void VertexArray::Bind() const
{
    GLCall(glBindVertexArray(m_RendererID));
}

void VertexArray::Unbind() const
{
    GLCall(glBindVertexArray(0));
}
