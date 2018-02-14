#include "VertexData.h"

VertexData::VertexData()
{
    glGenVertexArrays(1, &handle);
}

VertexData::~VertexData()
{
    //TODO: Delete all buffers
    glDeleteVertexArrays(1, &handle);
}

void VertexData::put(GUInt attribIndex, vec3 *data, int length)
{
    GLfloat *rawData = new GLfloat[length*3];
	for(int i; i<length; i++)
	{
		rawData[i*3] = data[i][0];
		rawData[i*3+1] = data[i][1];
		rawData[i*3+2] = data[i][2];
	} 

    GLuint vb;
    glGenBuffers(1, &vb);
    glBindBuffer(GL_ARRAY_BUFFER, vb);
    glBufferData(GL_ARRAY_BUFFER, 3* length * sizeof(GFloat), rawData, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, NULL);
    
    inputs[attribIndex] = vb;
}

void VertexData::index(GUInt *data, int length)
{
    GLuint ib;
    glGenBuffers(1, &ib);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, length * sizeof(GUInt), data, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
    
    indexBuffer = ib;
    this->length = length;
}

void VertexData::pack()
{
    glBindVertexArray(handle);
    
    map<GUInt, GUInt>::iterator it;
    for (it = inputs.begin(); it != inputs.end(); it++)
    {
        glEnableVertexAttribArray(it->first);
        glBindBuffer(GL_ARRAY_BUFFER, it->second);
        glVertexAttribPointer(it->first, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), NULL );
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

    glBindVertexArray(NULL);
}