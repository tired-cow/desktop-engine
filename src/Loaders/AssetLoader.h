#ifndef _ASSET_LOADER_H_
#define _ASSET_LOADER_H_

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include "Renderer/Mesh.h"

class AssetLoader
{
public:
	AssetLoader(const AssetLoader&) = delete;
	static AssetLoader& GetInstance();
	[[nodiscard]] Mesh LoadVerticesFromFile(const std::string&) const;
	[[nodiscard]] std::string const LoadShaderFromFile(const std::string&) const;

protected:
	static AssetLoader m_Instance;

private:
	AssetLoader() = default;
};

#endif