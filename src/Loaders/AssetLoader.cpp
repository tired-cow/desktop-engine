#include "AssetLoader.h"

AssetLoader AssetLoader::m_Instance;

AssetLoader &AssetLoader::GetInstance()
{
	return m_Instance;
}

Mesh AssetLoader::LoadMeshFromFile(const std::string &filePath) const
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
	{
		std::cout << "No meshes found!";
		exit(1);
	}

	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	std::vector<float> normals;
	std::vector<float> textureCoords;

	for (unsigned int i = 0; i < nMeshes; i++)
	{
		aiMesh *mesh = scene->mMeshes[i];
		for (unsigned int j = 0; j < mesh->mNumVertices; j++)
		{
			aiVector3D vertex = mesh->mVertices[j];
			vertices.push_back(vertex.x);
			vertices.push_back(vertex.y);
			vertices.push_back(vertex.z);
		}

		if (mesh->HasFaces())
		{
			for (unsigned int j = 0; j < mesh->mNumFaces; j++)
			{
				aiFace face = mesh->mFaces[j];
				for (unsigned int k = 0; k < face.mNumIndices; k++)
					indices.push_back(face.mIndices[k]);
			}
		}

		
		if (mesh->HasNormals())
		{
			for (unsigned int j = 0; j < mesh->mNumFaces; j++)
			{
				aiVector3D normal = mesh->mNormals[j];
				normals.push_back(normal.x);
				normals.push_back(normal.y);
				normals.push_back(normal.z);
			}
		}
		

		if (mesh->HasTextureCoords(0))
		{
			for (unsigned int j = 0; j < mesh->mNumVertices; j++)
			{
				aiVector3D coords = mesh->mTextureCoords[0][j];
				textureCoords.push_back(coords.x);
				textureCoords.push_back(coords.y);
				//textureCoords.push_back(coords.z);
			}
		}
		else
		{
			std::cout << "NO COORDS\n" << mesh->mTextureCoords[1] << "\n";
		}
	}
	
	return Mesh(vertices, indices, normals, textureCoords);
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
