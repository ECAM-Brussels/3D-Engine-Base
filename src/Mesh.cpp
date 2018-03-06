#include "mesh.h"
#include <fstream>
#include <sstream>
#include <iostream>

Mesh* Mesh::fromOBJ(string path)
{
    Mesh* mesh = new Mesh();
    ifstream file(path);

    for(string line; getline(file, line); )
    {
        if(line.size() == 0) continue;

        istringstream str(line);

        char cmd;

        switch(line[0])
        {
            case 'v':
                GLfloat x, y, z;
                str >> cmd >> x >> y >> z;
                mesh->vertexData.push_back(vec3(x, y, z));
            break;
            case 'f':
                GLuint v1, v2, v3;
                str >> cmd >> v1 >> v2 >> v3;
                mesh->indexData.push_back(v1-1);
                mesh->indexData.push_back(v2-1);
                mesh->indexData.push_back(v3-1);
            break;
        }
    }

    mesh->computeNormal();

    return mesh;
}

vec3* Mesh::getVertex()
{
    return vertexData.data();
}

GLuint* Mesh::getIndex()
{
    return indexData.data();
}

vec3* Mesh::getNormal()
{
    return normalData.data();
}

size_t Mesh::getVertexCount()
{
    return vertexData.size();
}

size_t Mesh::getIndexCount()
{
    return indexData.size();
}

size_t Mesh::getNormalCount()
{
    return normalData.size();
}

void Mesh::computeNormal()
{
    for(int i = 0; i < getVertexCount(); i++)
    {
        normalData.push_back(vec3(0, 0, 0));
    }

    for(int i = 0; i < getIndexCount()/3; i++)
    {
        vec3 faceNormal = normalize(cross(
            vertexData[indexData[i]]-vertexData[indexData[i+1]],
            vertexData[indexData[i]]-vertexData[indexData[i+2]]
        ));

        normalData[indexData[i]] += faceNormal;
        normalData[indexData[i+1]] += faceNormal;
        normalData[indexData[i+2]] += faceNormal;
    }

    for(int i = 0; i < getVertexCount(); i++)
    {
        normalData[i] = normalize(normalData[i]);
    }
}
