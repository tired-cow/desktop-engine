#pragma once

#include <GL/glew.h>
#include <iostream>
#include <fstream>

class Shader {
private:
    GLuint shader_id;
    GLenum shader_type;

    std::string shader_src;
    void get_src_from_file(const char*);

public:
    Shader(GLenum, const char*);
    Shader();
    ~Shader();
    bool compile();
    GLuint get_shader_id();
    GLenum get_shader_type();
};