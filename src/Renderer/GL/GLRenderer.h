#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <vector>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

#include "Loaders/AssetLoader.h"
#include "Renderer/IRenderer.h"

#include "GLVertexBuffer.h"
#include "GLVertexArray.h"
#include "GLIndexBuffer.h"
#include "GLShaderProgram.h"
#include "GLShader.h"

class GLRenderer : public IRenderer
{
public:
	GLRenderer();
	void Render(const Mesh&) override;
	void SetShaderProgram();

protected:
	GLShaderProgram m_ShaderProgram;
};

#endif