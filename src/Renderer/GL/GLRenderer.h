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

#include "World/WorldObject.h"
#include "GLVertexBuffer.h"
#include "GLVertexArray.h"
#include "GLIndexBuffer.h"
#include "GLMeshShader.h"
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
		// const GLShaderProgram *m_ShaderProgram;
		const GLMeshShader *m_MeshShader;
	};

public:
	void Render();
	void AddToRenderList(const WorldObject&, const GLMeshShader&);
	// void AddToRenderList(const Mesh&) override;
	// void AddToRenderList(const Mesh&, const GLShaderProgram&);

protected:
	std::unordered_map<const WorldObject *, GLRendererRenderData>  m_RendererDataMap;
	// std::unordered_map<const Mesh *, GLRendererRenderData>  m_RendererDataMap;
};

#endif