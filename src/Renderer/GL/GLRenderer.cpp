#include "GLRenderer.h"

GLRenderer::GLRenderer()
	: IRenderer()
{

}

void GLRenderer::Render(const Mesh &mesh)
{
	if (m_WorldCamera == nullptr)
		throw "World camera not set!";
	
	unsigned int projMatId = m_ShaderProgram.GetUniformLocation("projection");
	glm::mat4 projMat = glm::mat4(1.0f);
	projMat = glm::perspective(m_WorldCamera->m_FOV, m_WorldCamera->m_AspectRatio, m_WorldCamera->m_NearPlane, m_WorldCamera->m_FarPlane);
	glUniformMatrix4fv(projMatId, 1, GL_FALSE, glm::value_ptr(projMat));

	unsigned int modelMatId = m_ShaderProgram.GetUniformLocation("model");
	glm::mat4 modelMat = glm::mat4(1.0f);
	modelMat = glm::translate(modelMat, glm::vec3(0, 0, -15.5f));
	glUniformMatrix4fv(modelMatId, 1, GL_FALSE, glm::value_ptr(modelMat));

	GLVertexBuffer vBuff(mesh.GetVertices());
	GLIndexBuffer iBuff(mesh.GetIndices());
	GLVertexArray vArr;

	vArr.Bind();
	vArr.VertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (const void*)0);

	vBuff.Bind();
	iBuff.Bind();

	static const float black[] = {0.0f, 0.0f, 0.0f, 0.0f};
	glClearBufferfv(GL_COLOR, 0, black);

	glDrawElements(GL_TRIANGLES, mesh.GetIndices().size(), GL_UNSIGNED_INT, (void*)0);
}

void GLRenderer::SetShaderProgram()
{
	AssetLoader &assetLoader = AssetLoader::GetInstance();

	std::string vShaderSrc = assetLoader.LoadShaderFromFile("vertex.glsl");
	GLShader vertexShader(GL_VERTEX_SHADER);
	vertexShader.SourceShader(vShaderSrc);
	
	bool success = vertexShader.Compile();
	if (!success)
		throw "Vertex Shader failed to compile!";

	std::string fShaderSrc = assetLoader.LoadShaderFromFile("fragment.glsl");
	GLShader fragmentShader(GL_FRAGMENT_SHADER);
	fragmentShader.SourceShader(fShaderSrc);

	success = fragmentShader.Compile();
	if (!success)
		throw "Fragment Shader failed to compile!";

	
	m_ShaderProgram.SetShader(vertexShader);
	m_ShaderProgram.SetShader(fragmentShader);

	m_ShaderProgram.Use();
}
