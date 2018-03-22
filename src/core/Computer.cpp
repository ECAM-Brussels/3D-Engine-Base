#include "Computer.h"
#include "Exception.h"
#include <sstream>

using namespace std;

Computer::Computer(Program* program)
{
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 0, &workgroup_count[0]);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 1, &workgroup_count[1]);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 2, &workgroup_count[2]);

    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 0, &workgroup_size[0]);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 1, &workgroup_size[1]);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 2, &workgroup_size[2]);

    glGetIntegerv (GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS, &workgroup_invocations);

    this->program = program->getName();
}

void Computer::setData(int index, Buffer* data)
{
    // get Attrib handle
    //GInt attribLocation = glGetAttribLocation(program, attrib.c_str());

    glUseProgram(program);
    // Add buffer to vertexArray 
    //glBindVertexArray(vertexArray);
    //glEnableVertexAttribArray(attribLocation);
    //glBindBuffer(GL_SHADER_STORAGE_BUFFER, data->getName());
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, index, data->getName());
    
    //glVertexAttribPointer(attribLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), NULL );
    //glBindVertexArray(NULL);
    glUseProgram(NULL);
}

void Computer::compute(int count_x, int count_y, int count_z)
{
    glUseProgram(program);
    glDispatchCompute(count_x, count_y, count_z);
    glUseProgram(NULL);
}