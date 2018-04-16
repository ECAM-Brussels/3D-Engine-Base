#include "Mesh.h"
#include <fstream>
#include <sstream>
#include <iostream>

Mesh::Mesh(Buffer* vertex, size_t vertexCount, Buffer* index, size_t indexCount)
{
    vertexData = vertex;
    indexData = index;
    this->vertexCount = vertexCount;
    this->indexCount = indexCount;
}

Mesh::~Mesh()
{
    if(indexData) delete indexData;
    if(vertexData) delete vertexData;
}

Mesh* Mesh::fromOBJ(string path)
{
    vector<VertexData> vertex;
    vector<GUInt> index;
    
    ifstream file(path);

    for(string line; getline(file, line); )
    {
        if(line.size() == 0) continue;

        istringstream str(line);

        char cmd;

        switch(line[0])
        {
            case 'v':
                GFloat x, y, z;
                str >> cmd >> x >> y >> z;
                vertex.push_back(VertexData(vec3(x, y, z), vec3(0)));
            break;
            case 'f':
                GUInt v1, v2, v3;
                str >> cmd >> v1 >> v2 >> v3;
                index.push_back(v1-1);
                index.push_back(v2-1);
                index.push_back(v3-1);
            break;
        }
    }

    for(int i = 0; i < index.size()/3; i++)
    {
        vec3 faceNormal = normalize(cross(
            vertex[index[3*i+1]].position-vertex[index[3*i]].position,
            vertex[index[3*i+2]].position-vertex[index[3*i]].position
        ));

        vertex[index[3*i]].normal += faceNormal;
        vertex[index[3*i+1]].normal += faceNormal;
        vertex[index[3*i+2]].normal += faceNormal;
    }

    for(int i = 0; i < vertex.size(); i++)
    {
        vertex[i].normal = normalize(vertex[i].normal);
    }

    Mesh* mesh = new Mesh(
        new Buffer(vertex.data(), vertex.size()*sizeof(VertexData)), vertex.size(),
        new Buffer(index.data(), index.size()*sizeof(GUInt)), index.size()
    );

    return mesh;
}

Buffer* Mesh::getVertex()
{
    return vertexData;
}

Buffer* Mesh::getIndex()
{
    return indexData;
}

size_t Mesh::getVertexCount()
{

}

size_t Mesh::getIndexCount()
{

}
