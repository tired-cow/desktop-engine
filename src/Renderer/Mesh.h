#ifndef _MESH_H_
#define _MESH_H_

#include <vector>

class Mesh 
{
public:
	Mesh() = default;
	Mesh(const std::vector<float>&, const std::vector<unsigned int>&);

	void SetVertices(const std::vector<float>&);
	void SetIndices(const std::vector<unsigned int>&);
	const std::vector<float>& GetVertices() const;
	const std::vector<unsigned int>& GetIndices() const;

protected:
	std::vector<float> m_Vertices;
	std::vector<unsigned int> m_Indices;
};

#endif