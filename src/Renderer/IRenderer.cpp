#include "IRenderer.h"

IRenderer::IRenderer()
	: m_WorldCamera{nullptr}
{
}

void IRenderer::AddToRenderList(const Mesh &mesh)
{
	m_RenderList.push_back(&mesh);
}

void IRenderer::SetWorldCamera(WorldCamera *const camera)
{
	m_WorldCamera = camera;
}
