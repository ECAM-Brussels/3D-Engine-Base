#ifndef RENDERER_H
#define RENDERER_H

#include "opengl.h"
#include <string>
#include <vector>
#include "Shader.h"
#include "VertexData.h"

using namespace std;



class Renderer
{
private:
    GLuint handle;

public:
    Renderer(vector<Shader*> &shaders);
    ~Renderer();
    void render(VertexData &inputs);
};



#endif