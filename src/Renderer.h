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
    GLuint vertexDataLength;

public:
    Renderer(vector<Shader*> &shaders);
    ~Renderer();
    void render();
    void setVertexData(VertexData &inputs);
    void setProjectionMatrix(mat4 pM);
    void setModelViewMatrix(mat4 mV);
};



#endif