#pragma once

#include "Component.h"
#include "Mesh.h"
#include <string>
#include <vector>

class ModelComponent : Component {
protected:
  std::vector<Mesh> meshes;

public:
  ModelComponent() = default;
  void load_model(const std::string&);
};