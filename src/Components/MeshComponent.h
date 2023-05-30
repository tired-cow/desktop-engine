#ifndef _MESH_COMPONENT_H_
#define _MESH_COMPONENT_H_

#include "Component.h"
#include "Renderer/Mesh.h"

class MeshComponent : public Component
{
public:
	

public:
	MeshComponent();

protected:
	Mesh m_Mesh;
};

#endif