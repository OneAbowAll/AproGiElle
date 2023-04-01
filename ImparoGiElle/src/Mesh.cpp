#include "Mesh.h"

Mesh::Mesh(const std::vector<Vertex>& positions, const std::vector<unsigned int>& indices)
	:m_VAO(), m_VBO(&positions[0], positions.size() * sizeof(Vertex)), m_IBO(&indices[0], indices.size())
{
	m_VAO.AddBuffer(m_VBO);
}

Mesh::~Mesh()
{
}
