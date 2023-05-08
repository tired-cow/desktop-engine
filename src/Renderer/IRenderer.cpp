#include "IRenderer.h"

IRenderer::IRenderer()
	: m_WorldCamera{nullptr}
{
}

void IRenderer::SetWorldCamera(WorldCamera *const camera)
{
	m_WorldCamera = camera;
}
