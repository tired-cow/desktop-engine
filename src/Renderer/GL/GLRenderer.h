#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <vector>
#include <unordered_map>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

#include "Loaders/AssetLoader.h"
#include "Renderer/IRenderer.h"
#include "Renderer/Mesh.h"

#include "GLVertexBuffer.h"
#include "GLVertexArray.h"
#include "GLIndexBuffer.h"
#include "GLShaderProgram.h"
#include "GLShader.h"

class GLRenderer : public IRenderer
{
public:
	struct GLRendererRenderData
	{
		GLVertexArray m_VertexArray;
		GLIndexBuffer m_IndexBuffer;
		GLVertexBuffer m_VertexBuffer;
		GLShaderProgram m_ShaderProgram;
	};

public:
	void Render();
	void AddToRenderList(const Mesh&) override;
	void AddToRenderList(const Mesh&, const GLShaderProgram&);

protected:
	//void SetupDefaultShader();

protected:
	std::unordered_map<const Mesh *, GLRendererRenderData>  m_RendererDataMap;
	//GLShaderProgram m_DefaultProgram;
};

#endif