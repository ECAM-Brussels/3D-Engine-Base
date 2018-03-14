#ifndef RENDERER_H
#define RENDERER_H

#include "opengl.h"
#include "vmath.h"
#include <vector>
#include <string>

using namespace std;
using namespace vmath;

class Program;

class Renderer
{
private:
    GUInt program;
    GUInt indexLength;
    GUInt vertexArray;
    vector<GUInt> buffers;

public:
    Renderer(Program* program);
    ~Renderer();
    void put(string attrib, vec3 *data, int length);
    void index(GUInt *data, int length);
    void render();
    void setMatrix(string attrib, mat4 pM);
};

#endif