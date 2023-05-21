#ifndef _WORLD_OBJECT_H_
#define _WORLD_OBJECT_H_

#include "Node.h"
#include "Renderer/Mesh.h"
#include "Math/Vector3.hpp"
#include <vector>

class WorldObject : public Node
{
public:
	Vector3 m_Position;
	Vector3 m_Rotation;

	Mesh m_Mesh;
};

#endif