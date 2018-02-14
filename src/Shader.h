#ifndef SHADER_H
#define SHADER_H

#include "opengl.h"
#include <string>

using namespace std;

enum ShaderType
{ 
    SHADER_VERTEX = GL_VERTEX_SHADER,
    SHADER_PIXEL = GL_FRAGMENT_SHADER
};

class Shader
{
friend class Renderer;
protected:
    GLuint handle;
public:
    Shader(string src, ShaderType type);
    ~Shader();
};

#endif