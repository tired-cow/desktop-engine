#include "GLMeshShader.h"

void GLMeshShader::Use() const
{
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

	m_ShaderProgram.SetShader(*m_ShaderMap[GLShaderType]);
}


// Should probably be replaced with something else
// if you want to set uniforms
const GLShaderProgram &GLMeshShader::GetShaderProgram() const
{
	return m_ShaderProgram;
}

GLMeshShader::GLMeshShader()
	: m_ShaderProgram(), m_AssetLoader{AssetLoader::GetInstance()}
{

}