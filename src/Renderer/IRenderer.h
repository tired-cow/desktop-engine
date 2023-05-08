#ifndef _I_RENDERER_H_
#define _I_RENDERER_H_

#include "Mesh.h"
#include "World/WorldCamera.h"

class IRenderer
{
public:
	IRenderer();
	virtual void Render(const Mesh&) = 0;
	void SetWorldCamera(WorldCamera *const camera);

protected:
	WorldCamera *m_WorldCamera;
};
#endif