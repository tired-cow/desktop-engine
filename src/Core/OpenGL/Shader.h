#pragma once

#include "GLObject.h"
#include <GL/glew.h>
#include <iostream>
#include <fstream>

class Shader : public GLObject {
private:
    GLenum shader_type;

    std::string shader_src;
    void get_src_from_file(const char*);

public:
    Shader(GLenum, const char*);
    Shader();
    ~Shader();
    bool compile();
    GLenum get_shader_type();
};