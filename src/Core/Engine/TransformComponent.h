#pragma once
#include "Component.h"
#include "Object.h"
#include "Math/Vector3.hpp"

class TransformComponent : public Component {
public:
  Vector3 position;
  Vector3 rotation;

  TransformComponent(Object*);
};