#include "Mesh.h"

Mesh::Mesh(const std::vector<float> &v, const std::vector<unsigned int> &i)
{
	SetVertices(v);
	SetIndices(i);
}

void Mesh::SetVertices(const std::vector<float> &v)
{
	m_Vertices = std::move(v);
}

void Mesh::SetIndices(const std::vector<unsigned int> &i)
{
	m_Indices = std::move(i);
}

const std::vector<float> &Mesh::GetVertices() const
{
	return m_Vertices;
}

const std::vector<unsigned int> &Mesh::GetIndices() const
{
	return m_Indices;
}
