#pragma once

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include "OpenGL/VertexBuffer.h"
#include "OpenGL/IndexBuffer.h"


class Mesh {
private:
  std::vector<float> vertcies;
  std::vector<unsigned int> indices;

  VertexBuffer vertex_buffer;
  IndexBuffer index_buffer;

public:
  Mesh(aiMesh*);
};