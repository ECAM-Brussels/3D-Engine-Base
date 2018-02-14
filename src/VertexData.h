#ifndef VERTEXDATA_H
#define VERTEXDATA_H

#include "opengl.h"
#include <map>
#include "vmath.h"

using namespace std; 
using namespace vmath;

class VertexData
{
friend class Renderer;
private:
    map<GUInt, GUInt> inputs;
    GLuint indexBuffer;
    GLuint handle;
    int length;

public:
    VertexData();
    ~VertexData();
    void put(GUInt attribIndex, vec3 *data, int length);
    void index(GUInt *data, int length);
    void pack();
};

//TODO: Add a warning when using an unpacked VertexData

#endif