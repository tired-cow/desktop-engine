#ifndef _WORLD_CAMERA_H_
#define _WORLD_CAMERA_H_

#include "WorldObject.h"

class WorldCamera : public WorldObject
{
public:
	WorldCamera(float FOV = 30.0f, float AspectRatio = (float)1920/1080, float NearPlane = .1f, float FarPlane = 100.0f);

public:
	float m_FOV;
	float m_NearPlane;
	float m_FarPlane;
	float m_AspectRatio;
};

#endif