#pragma once

#include <vector>

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Vertex.h"

class Mesh
{
public:
	Mesh(const std::vector<Vertex>& positions, const std::vector<unsigned int>& indices);
	~Mesh();

	VertexArray m_VAO;
	VertexBuffer m_VBO;
	IndexBuffer m_IBO;

private:
};