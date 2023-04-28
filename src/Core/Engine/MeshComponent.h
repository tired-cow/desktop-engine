#pragma once

#include "OpenGL/VertexBuffer.h"
#include "OpenGL/VertexArray.h"
#include "OpenGL/IndexBuffer.h"
#include "Component.h"
#include <vector>

class MeshComponent : Component {
private:
  static void load_verticies_from_obj(const char *file_name, std::vector<float>&, std::vector<unsigned int>&);


protected:
  VertexArray vertex_array;
  VertexBuffer vertex_buffer;

public:
  MeshComponent() = default;
  void load_model(const char*);
};