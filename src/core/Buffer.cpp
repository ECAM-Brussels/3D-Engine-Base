#include "Buffer.h"
#include <iostream>

using namespace std;

Buffer::Buffer(void* data, size_t size)
{
    glGenBuffers(1, &buffer);

    glBindBuffer(GL_SHADER_STORAGE_BUFFER, buffer);
    glBufferData(GL_SHADER_STORAGE_BUFFER, size, data, GL_DYNAMIC_COPY);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, NULL);

    this->size = size;
}

Buffer::~Buffer()
{
    glDeleteBuffers(1, &buffer);
}

GUInt Buffer::getName()
{
    return buffer;
}