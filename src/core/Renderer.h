#ifndef RENDERER_H
#define RENDERER_H

#include "opengl.h"
#include "vmath.h"
#include <vector>
#include <string>

using namespace std;
using namespace vmath;

enum Primitive
{
    PRIMITIVE_TRIANGLES = GL_TRIANGLES,
    PRIMITIVE_POINTS = GL_POINTS
};

enum ComponentType
{
    TYPE_FLOAT = GL_FLOAT,
    TYPE_INT = GL_INT,
    TYPE_UINT = GL_UNSIGNED_INT,
    TYPE_DOUBLE = GL_DOUBLE
};

class Program;
class Buffer;
class Renderer
{
private:
    GUInt program;
    GUInt vertexArray;

public:
    Renderer(Program* program);
    ~Renderer();

    void setVertexData(string attrib, Buffer* data, ComponentType type, int offset, int dimension, int stride);

    void setMatrix(string attrib, mat3 m);
    void setMatrix(string attrib, mat4 m);
    void setVec(string attrib, vec2 v);
    void setVec(string attrib, vec3 v);
    void setVec(string attrib, vec4 v);
    void setScal(string attrib, float f);
    void index(Buffer* index);
    void render(Primitive primitive, size_t count);
    void indexedRender(Primitive primitive, size_t count);
};

#include "Buffer.h"

#endif