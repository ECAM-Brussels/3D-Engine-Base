#include "Renderer.h"
#include "Exception.h"
#include "Program.h"
#include <sstream>

Renderer::Renderer(Program* program)
{
    this->program = program->getName();
    glGenVertexArrays(1, &vertexArray);
}

Renderer::~Renderer()
{
    glDeleteVertexArrays(1, &vertexArray);
}

void Renderer::setVertexData(string attrib, Buffer* data, ComponentType type, int offset, int dimension, int stride)
{
    GUInt attribLocation = glGetAttribLocation(program, attrib.c_str());

    // Add buffer to vertexArray 
    glBindVertexArray(vertexArray);
    glEnableVertexAttribArray(attribLocation);
    glBindBuffer(GL_ARRAY_BUFFER, data->getName());
    glVertexAttribPointer(attribLocation, dimension, type, GL_FALSE, stride, (GLvoid*) offset);
    glBindVertexArray(NULL);
}

void Renderer::setMatrix(string attrib, mat3 pM)
{
    glUseProgram(program);
    glUniformMatrix3fv(glGetUniformLocation(program, attrib.c_str()), 1, GL_FALSE, pM);
    glUseProgram(0);
}

void Renderer::setMatrix(string attrib, mat4 pM)
{
    glUseProgram(program);
    glUniformMatrix4fv(glGetUniformLocation(program, attrib.c_str()), 1, GL_FALSE, pM);
    glUseProgram(0);
}

void Renderer::setVec(string attrib, vec2 v)
{
    glUseProgram(program);
    glUniform2fv(glGetUniformLocation(program, attrib.c_str()), 1, v);
    glUseProgram(0);
}

void Renderer::setVec(string attrib, vec3 v)
{
    glUseProgram(program);
    glUniform3fv(glGetUniformLocation(program, attrib.c_str()), 1, v);
    glUseProgram(0);
}

void Renderer::setVec(string attrib, vec4 v)
{
    glUseProgram(program);
    glUniform4fv(glGetUniformLocation(program, attrib.c_str()), 1, v);
    glUseProgram(0);
}

void Renderer::render(Primitive primitive, size_t count)
{
    glUseProgram(program);

    glBindVertexArray(vertexArray);
    glDrawArrays(primitive, 0, count);

    glUseProgram(0);
}

void Renderer::index(Buffer* index)
{
    glBindVertexArray(vertexArray);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index->getName());
    glBindVertexArray(NULL);
}

void Renderer::indexedRender(Primitive primitive, size_t count)
{
    glUseProgram(program);

    glBindVertexArray(vertexArray);
    glDrawElements(primitive, count, GL_UNSIGNED_INT, NULL);

    glUseProgram(0);
}


