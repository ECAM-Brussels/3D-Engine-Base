#include "Renderer.h"
#include "Exception.h"
#include "Program.h"
#include <sstream>

Renderer::Renderer(Program* program)
{
    this->program = program->program;
    glGenVertexArrays(1, &vertexArray);
}

Renderer::~Renderer()
{
    glDeleteVertexArrays(1, &vertexArray);

    for(int i = 0; i < buffers.size(); i++)
    {
        glDeleteBuffers(1, &buffers[i]);
    }
}

void Renderer::put(string attrib, vec3 *data, int length) 
{
    // Create Buffer
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

    // save buffer handle
    buffers.push_back(vb);

    // get Attrib handle
    GInt attribLocation = glGetAttribLocation(program, attrib.c_str());

    // Add buffer to vertexArray 
    glBindVertexArray(vertexArray);
    glEnableVertexAttribArray(attribLocation);
    glBindBuffer(GL_ARRAY_BUFFER, vb);
    glVertexAttribPointer(attribLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), NULL );
    glBindVertexArray(NULL);
}

void Renderer::index(GUInt *data, int length)
{
    GLuint ib;
    glGenBuffers(1, &ib);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, length * sizeof(GUInt), data, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
    
    buffers.push_back(ib);
    indexLength = length;

    // Add buffer to vertexArray 
    glBindVertexArray(vertexArray);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
    glBindVertexArray(NULL);
}

void Renderer::render()
{
    glUseProgram(program);

    glBindVertexArray(vertexArray);
    glDrawElements(GL_TRIANGLES, indexLength, GL_UNSIGNED_INT, NULL);

    glUseProgram(0);
}

void Renderer::setMatrix(string attrib, mat4 pM)
{
    glUseProgram(program);
    glUniformMatrix4fv(glGetUniformLocation(program, attrib.c_str()), 1, GL_FALSE, pM);
    glUseProgram(0);
}
