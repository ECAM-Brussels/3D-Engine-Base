#include "mesh.h"
#include <fstream>
#include <sstream>

Mesh* Mesh::fromOBJ(string path)
{
    Mesh* mesh = new Mesh();
    ifstream file(path);

    for(string line; getline(file, line); )
    {
        istringstream str(line);

        switch(line[0])
        {
            case 'v':
                GLfloat x, y, z;
                str >> x >> y >> z;
                mesh->vertexData.push_back(vec3(x, y, z));
            break;
            case 'f':
                GLint v1, v2, v3;
                str >> v1 >> v2 >> v3;
                mesh->indexData.push_back(v1);
                mesh->indexData.push_back(v2);
                mesh->indexData.push_back(v3);
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

GLint* Mesh::getIndex()
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
