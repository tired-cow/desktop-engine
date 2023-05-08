#include "AssetLoader.h"

AssetLoader AssetLoader::m_Instance;

AssetLoader &AssetLoader::GetInstance()
{
	return m_Instance;
}

Mesh* AssetLoader::LoadVerticesFromFile(const std::string &filePath) const
{
	Assimp::Importer importer;

	const aiScene *scene = importer.ReadFile(filePath,
    aiProcess_CalcTangentSpace       |
    aiProcess_Triangulate            |
    aiProcess_JoinIdenticalVertices  |
    aiProcess_SortByPType);

	if (nullptr == scene)
	{
		std::cout << importer.GetErrorString() << std::endl;
		exit(1);
	}

	unsigned int nMeshes = scene->mNumMeshes;
  	if (nMeshes <= 0)
		throw "No meshes found!";
	
	std::vector<float> vertices;
	std::vector<unsigned int> indices;

	for (unsigned int i = 0; i < nMeshes; i++)
	{
		aiMesh *mesh = scene->mMeshes[i];
		vertices.reserve(mesh->mNumVertices * 3);
		for (unsigned int j = 0; j < mesh->mNumVertices; j++)
		{
			aiVector3D vertex = mesh->mVertices[j];
			vertices.push_back(vertex.x);
			vertices.push_back(vertex.y);
			vertices.push_back(vertex.z);
		}
		
		if (!(mesh->HasFaces()))
			break;

		for (unsigned int j = 0; j < mesh->mNumFaces; j++)
		{
			aiFace face = mesh->mFaces[j];
			if (face.mNumIndices > 3)
				throw "Uhh more than 3 indices, can't render that!";

			for (unsigned int k = 0; k < face.mNumIndices; k++)
				indices.push_back(face.mIndices[k]);
		}
	}
	
	return new Mesh(vertices, indices);
}

std::string const AssetLoader::LoadShaderFromFile(const std::string &path) const
{
	std::ifstream ifs(path.c_str());
	std::string str = std::string(
		(std::istreambuf_iterator<char>(ifs)),
		(std::istreambuf_iterator<char>())
	);

	if (str.empty())
		throw "No file!";

	return str;
}
