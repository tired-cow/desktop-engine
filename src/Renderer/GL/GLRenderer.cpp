#include "GLRenderer.h"

void GLRenderer::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (const auto &keyValue : m_RendererDataMap)
	{
		const Mesh &mesh = *(keyValue.first);
		const GLVertexArray &va = keyValue.second.m_VertexArray;
		va.Bind();
		glDrawElements(GL_TRIANGLES, mesh.GetIndices().size(), GL_UNSIGNED_INT, (void*)0);
	}
	
	
}

void GLRenderer::AddToRenderList(const Mesh &mesh)
{
	// Setup default Shader
	AssetLoader &assetLoader = AssetLoader::GetInstance();

	std::string vShaderSrc = assetLoader.LoadShaderFromFile("assets/vertex.glsl");
	GLShader vertexShader(GL_VERTEX_SHADER);
	vertexShader.SourceShader(vShaderSrc);
	bool success = vertexShader.Compile();
	if (!success)
	{
		std::cout << "Vertex Shader failed to compile!\n";
		exit(1);
	}

	std::string fShaderSrc = assetLoader.LoadShaderFromFile("assets/fragment.glsl");
	GLShader fragmentShader(GL_FRAGMENT_SHADER);
	fragmentShader.SourceShader(fShaderSrc);
	success = fragmentShader.Compile();
	if (!success)
	{
		std::cout << "Fragment Shader failed to compile!\n";
		exit(1);
	}

	GLShaderProgram shaderProgram;
	shaderProgram.SetShader(vertexShader);
	shaderProgram.SetShader(fragmentShader);
	//

	AddToRenderList(mesh, shaderProgram);
}

void GLRenderer::AddToRenderList(const Mesh &mesh, const GLShaderProgram &shaderProgram)
{
	m_RendererDataMap[&mesh];
	GLRendererRenderData& data = m_RendererDataMap[&mesh];

	data.m_VertexArray.Bind();

	data.m_VertexBuffer.BufferData(mesh.GetVertices());
	data.m_VertexBuffer.Bind();

	data.m_IndexBuffer.BufferData(mesh.GetIndices());
	data.m_IndexBuffer.Bind();

	data.m_VertexArray.AddVertexAttribute(3, GL_FLOAT);
}