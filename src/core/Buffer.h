#ifndef BUFFER_H
#define BUFFER_H

#include "opengl.h"
#include "vmath.h"

using namespace vmath;

class Buffer
{
private:
    GUInt buffer;
    size_t size;

public:
    Buffer(void* data, size_t size);
    ~Buffer();
    GUInt getName();
};

#endif