#ifndef _GL_MESH_SHADER_H_
#define _GL_MESH_SHADER_H_

#include "IMeshShader.h"
#include "GLObject.h"
#include "GLShader.h"
#include "GLShaderProgram.h"
#include "Loaders/AssetLoader.h"

#include <unordered_map>
#include <memory>
#include <string>

class GLMeshShader : public IMeshShader
{
public:
	void Use() override;
	void SetShader(unsigned int, const std::string&);

public:
	GLMeshShader();
	GLMeshShader(const GLMeshShader&) = delete;
	GLMeshShader& operator=(const GLMeshShader&) = delete;

protected:
	AssetLoader &m_AssetLoader;
	std::unordered_map<unsigned int, std::unique_ptr<GLShader>> m_ShaderMap;
	GLShaderProgram m_ShaderProgram;
};

#endif