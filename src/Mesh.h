#ifndef MESH_H
#define MESH_H

#include "vmath.h"
#include "string"
#include "opengl.h"
#include <vector>

using namespace std;
using namespace vmath;

class Mesh
{
private:
    vector<vec3> vertexData;
    vector<GLuint> indexData;
    vector<vec3> normalData;

public:
    static Mesh* fromOBJ(string path);
    void computeNormal();
    vec3* getVertex();
    GLuint* getIndex();
    vec3* getNormal();
    size_t getVertexCount();
    size_t getIndexCount();
    size_t getNormalCount();
    
};

#endif