#ifndef _WORLD_OBJECT_H_
#define _WORLD_OBJECT_H_

#include "Node.h"
#include "Renderer/Mesh.h"
#include "Math/Vector3.hpp"

class WorldObject : public Node
{
public:
	WorldObject();

	Vector3 m_Position;
	Vector3 m_Rotation;
};

#endif