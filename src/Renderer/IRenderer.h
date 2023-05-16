#ifndef _I_RENDERER_H_
#define _I_RENDERER_H_

#include <vector>
#include "Mesh.h"
#include "World/WorldCamera.h"

class IRenderer
{
public:
	IRenderer();
	virtual void Render() = 0;
	virtual void AddToRenderList(const Mesh&);
	void SetWorldCamera(WorldCamera *const camera);

protected:
	WorldCamera *m_WorldCamera;
	std::vector<Mesh const *> m_RenderList;
};
#endif