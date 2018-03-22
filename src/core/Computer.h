#ifndef COMPUTER_H
#define COMPUTER_H

#include "opengl.h"
#include "Shader.h"
#include "vmath.h"
#include <vector>

using namespace vmath;

class Program;
class Buffer;

class Computer
{
private:
    GUInt program;
    int workgroup_count[3];
    int workgroup_size[3];
    int workgroup_invocations;

public:
    Computer(Program* program);
    void setData(int index, Buffer* data);
    void compute(int count_x, int count_y, int count_z);
};

#include "Program.h"
#include "Buffer.h"

#endif