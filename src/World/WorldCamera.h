#ifndef _WORLD_CAMERA_H_
#define _WORLD_CAMERA_H_

#include "WorldObject.h"

class WorldCamera : public WorldObject
{
public:
	WorldCamera();

public:
	float m_FOV;
	float m_NearPlane;
	float m_FarPlane;
	float m_AspectRatio;
};

#endif