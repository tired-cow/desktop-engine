#include "Mesh.h"

Mesh::Mesh(const std::vector<float> &v, const std::vector<unsigned int> &i, const std::vector<float> &n)
{
	SetVertices(v);
	SetIndices(i);
	SetNormals(n);
}

void Mesh::SetVertices(const std::vector<float> &v)
{
	m_Vertices = std::move(v);
}

void Mesh::SetIndices(const std::vector<unsigned int> &i)
{
	m_Indices = std::move(i);
}

void Mesh::SetNormals(const std::vector<float> &n)
{
	m_Normals = std::move(n);
}

const std::vector<float>& Mesh::GetVertices() const
{
	return m_Vertices;
}

const std::vector<unsigned int>& Mesh::GetIndices() const
{
	return m_Indices;
}

const std::vector<float>& Mesh::GetNormals() const
{
	return m_Normals;
}
