#include "WorldCamera.h"

WorldCamera::WorldCamera()
{
	m_AspectRatio = (float)1920/1080;
	m_FOV = 30;
	m_NearPlane = .1f;
	m_FarPlane = 100.0f;

}