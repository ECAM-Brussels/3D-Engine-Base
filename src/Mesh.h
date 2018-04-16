#ifndef MESH_H
#define MESH_H

#include "core/vmath.h"
#include "string"
#include "core/opengl.h"
#include <vector>
#include "core/Buffer.h"

using namespace std;
using namespace vmath;

struct VertexData
{
    vec3 position;
    vec3 normal;
    VertexData(vec3 pos, vec3 norm)
    {
        position = pos;
        normal = norm;
    }
};

class Mesh
{
private:
    Buffer* vertexData = NULL;
    Buffer* indexData = NULL;
    size_t indexCount = 0;
    size_t vertexCount = 0;

public:
    Mesh(Buffer* vertex, size_t vertexCount, Buffer* index, size_t indexCount);
    ~Mesh();
    static Mesh* fromOBJ(string path);
    Buffer* getVertex();
    Buffer* getIndex();
    size_t getVertexCount();
    size_t getIndexCount();
    
};

#endif