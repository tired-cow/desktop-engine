#include "WorldCamera.h"

WorldCamera::WorldCamera(float FOV, float AspectRatio, float NearPlane, float FarPlane)
	: m_FOV{FOV}, m_AspectRatio{AspectRatio}, m_NearPlane{NearPlane}, m_FarPlane{FarPlane}
{
}
