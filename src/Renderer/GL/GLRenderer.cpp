#include "GLRenderer.h"

void GLRenderer::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (const auto &keyValue : m_RendererDataMap)
	{
		const WorldObject &worldObj = *(keyValue.first);
		const GLRendererRenderData& renderData = keyValue.second;
		renderData.m_VertexArray.Bind();
		renderData.m_MeshShader->Use();

		const GLShaderProgram &shaderProgram = renderData.m_MeshShader->GetShaderProgram();
		unsigned int MVPId = shaderProgram.GetUniformLocation("MVP");
		
		glm::mat4 MVPMat = glm::mat4(1.0f);
		MVPMat = glm::perspective(m_WorldCamera->m_FOV, m_WorldCamera->m_AspectRatio, m_WorldCamera->m_NearPlane, m_WorldCamera->m_FarPlane);
		MVPMat = glm::translate(MVPMat, glm::vec3(worldObj.m_Position.x, worldObj.m_Position.y, worldObj.m_Position.z));
		MVPMat = glm::rotate(MVPMat, worldObj.m_Rotation.x * (float)(3.14159265/180), glm::vec3(1, 0, 0));
		MVPMat = glm::rotate(MVPMat, worldObj.m_Rotation.y * (float)(3.14159265/180), glm::vec3(0, 1, 0));
		MVPMat = glm::rotate(MVPMat, worldObj.m_Rotation.z * (float)(3.14159265/180), glm::vec3(0, 0, 1));
		// MVPMat = glm::rotate(MVPMat, )
		glUniformMatrix4fv(MVPId, 1, GL_FALSE, glm::value_ptr(MVPMat));
		
		glDrawElements(GL_TRIANGLES, worldObj.m_Mesh.GetIndices().size(), GL_UNSIGNED_INT, (void*)0);
	}
}

void GLRenderer::AddToRenderList(const WorldObject &worldObj, const GLMeshShader &meshShader)
{
	// m_RendererDataMap[&worldObj];
	GLRendererRenderData &data = m_RendererDataMap[&worldObj];

	data.m_VertexArray.Bind();

	data.m_VertexBuffer.BufferData(worldObj.m_Mesh.GetVertices());
	data.m_VertexBuffer.Bind();

	data.m_IndexBuffer.BufferData(worldObj.m_Mesh.GetIndices());
	data.m_IndexBuffer.Bind();

	// Must be done after other bindings
	data.m_VertexArray.AddVertexAttribute(3, GL_FLOAT);
	data.m_MeshShader = &meshShader;
}