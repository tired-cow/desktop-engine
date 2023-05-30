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
		
		// Camera
		glm::mat4 projMat = glm::mat4(1.0f);
		projMat = glm::perspective(m_WorldCamera->m_FOV, m_WorldCamera->m_AspectRatio, m_WorldCamera->m_NearPlane, m_WorldCamera->m_FarPlane);
		projMat = glm::translate(projMat, glm::vec3(m_WorldCamera->m_Position.x, -m_WorldCamera->m_Position.y, m_WorldCamera->m_Position.z));
		projMat = glm::rotate(projMat, m_WorldCamera->m_Rotation.x * (float)(3.14159265/180), glm::vec3(1, 0, 0));
		projMat = glm::rotate(projMat, m_WorldCamera->m_Rotation.y * (float)(3.14159265/180), glm::vec3(0, 1, 0));
		projMat = glm::rotate(projMat, m_WorldCamera->m_Rotation.z * (float)(3.14159265/180), glm::vec3(0, 0, 1));

		// Model
		glm::mat4 modelMat = glm::mat4(1.0f);
		modelMat = glm::translate(modelMat, glm::vec3(worldObj.m_Position.x, -worldObj.m_Position.y, worldObj.m_Position.z));
		modelMat = glm::rotate(modelMat, worldObj.m_Rotation.x * (float)(3.14159265/180), glm::vec3(1, 0, 0));
		modelMat = glm::rotate(modelMat, worldObj.m_Rotation.y * (float)(3.14159265/180), glm::vec3(0, 1, 0));
		modelMat = glm::rotate(modelMat, worldObj.m_Rotation.z * (float)(3.14159265/180), glm::vec3(0, 0, 1));

		glUniformMatrix4fv(MVPId, 1, GL_FALSE, glm::value_ptr(projMat * modelMat));
		
		glDrawElements(GL_TRIANGLES, worldObj.m_Mesh.GetIndices().size(), GL_UNSIGNED_INT, (void*)0);
	}
}

void GLRenderer::AddToRenderList(const WorldObject &worldObj, const GLMeshShader &meshShader)
{
	GLRendererRenderData &data = m_RendererDataMap[&worldObj];

	data.m_VertexArray.Bind();

	std::vector<float> temp;
	FormatVertexData(worldObj.m_Mesh, temp);
	
	data.m_VertexBuffer.BufferData(temp);
	data.m_VertexBuffer.Bind();

	data.m_IndexBuffer.BufferData(worldObj.m_Mesh.GetIndices());
	data.m_IndexBuffer.Bind();

	// Must be done after other bindings
	data.m_VertexArray.AddVertexAttribute(3, GL_FLOAT);
	data.m_VertexArray.AddVertexAttribute(2, GL_FLOAT);
	data.m_MeshShader = &meshShader;
}

void GLRenderer::FormatVertexData(const Mesh &mesh, std::vector<float> &dataVec)
{
	const std::vector<float> &verts = mesh.GetVertices();
	const std::vector<float> &tCoords = mesh.GetTextureCoordinates();
	
	for (unsigned int vertIndex = 0; vertIndex < (verts.size() / 3); vertIndex++)
	{
		for (unsigned int vertPosComp = vertIndex*3; vertPosComp < vertIndex*3 + 3; vertPosComp++)
			dataVec.push_back(verts.at(vertPosComp));

		for (int tCoordComp = vertIndex * 2; tCoordComp < vertIndex*2 + 2; tCoordComp++)
			dataVec.push_back(tCoords.at(tCoordComp));
	}
}
