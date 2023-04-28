#include "ModelComponent.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <iostream>
#include <string>

void ModelComponent ::load_model(const std::string& file_path) {
  Assimp::Importer importer;

  const aiScene* scene = importer.ReadFile(file_path,
    aiProcess_CalcTangentSpace       |
    aiProcess_Triangulate            |
    aiProcess_JoinIdenticalVertices  |
    aiProcess_SortByPType);

  if (nullptr == scene) {
    std::cout << importer.GetErrorString() << std::endl;
    return;
  }

  aiNode *root_node = scene->mRootNode;
  for (unsigned int i = 0; i < root_node->mNumMeshes; i++) {
    Mesh m(scene->mMeshes[root_node->mMeshes[i]]);
  }
  
}