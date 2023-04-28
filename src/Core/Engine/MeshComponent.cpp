#include "MeshComponent.h"

void MeshComponent::load_verticies_from_obj(const char *file_name, std::vector<float>& verticies, std::vector<unsigned int>& indices) {
  std::ifstream file(file_name);

  std::string line;
  while (std::getline(file, line)) {
    std::istringstream line_stream(line);

    std::string line_cmd;
    line_stream >> line_cmd;

    std::string substr;
    while (getline(line_stream, substr, ' ')) {
        if (substr.length() == 0)
          continue;

        if (line_cmd == "v") {
          float i = std::stof(substr);
          verticies.push_back(i);
        } else if (line_cmd == "f") {
          unsigned int i = (int)substr.at(0) - 48;
          indices.push_back(i);
        }
    }
  }

  file.close();
}

MeshComponent::load_model(const char* file_path) {
  vertex_array.
}