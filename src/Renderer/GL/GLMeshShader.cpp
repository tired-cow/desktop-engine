#include "GLMeshShader.h"

void GLMeshShader::Use()
{
	for (const auto &key : m_ShaderMap)
	{
		m_ShaderProgram.SetShader(*key.second);
	}

	m_ShaderProgram.Use();
}

void GLMeshShader::SetShader(unsigned int GLShaderType, const std::string &filePath)
{
	m_ShaderMap[GLShaderType] = std::make_unique<GLShader>(GLShaderType);
	m_ShaderMap[GLShaderType]->SourceShader(m_AssetLoader.LoadShaderFromFile(filePath));
	m_ShaderMap[GLShaderType]->Compile();

	if (m_ShaderMap[GLShaderType]->IsCompiled() == false)
	{
		std::cout << "Failed to compile!\n";
		exit(1);
	}
}

GLMeshShader::GLMeshShader()
	: m_ShaderProgram(), m_AssetLoader{AssetLoader::GetInstance()}
{

}