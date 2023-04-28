#include "Mesh.h"

#include <vector>
#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

Mesh::Mesh(aiMesh *mesh) {
  for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
    vertcies.push_back(mesh->mVertices[i].x);
    vertcies.push_back(mesh->mVertices[i].y);
    vertcies.push_back(mesh->mVertices[i].z);
  }
  vertex_buffer = VertexBuffer(vertcies);

  if(!mesh->HasFaces()) {
    std::cout << "Mesh does not contain faces :(" << std::endl;
    return;
  }

  for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
    aiFace face = mesh->mFaces[i];
    for (unsigned int j = 0; j < face.mNumIndices; j++) {
      indices.push_back(face.mIndices[j]);
    }
  }
  index_buffer = IndexBuffer(indices);
}