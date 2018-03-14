#include "Program.h"
#include <sstream>
#include "Exception.h"

Program::Program()
{
    program = glCreateProgram();
}
Program::~Program()
{
    glDeleteProgram(program);
}
void Program::addShader(Shader* shader)
{
    if(compiled) throw Exception("Program already compiled");
    shaders.push_back(shader);
}

void Program::compile()
{
    if(compiled) throw Exception("Program already compiled");

    for(int i = 0; i < shaders.size(); i++)
    	glAttachShader(program, shaders[i]->handle);
    
    glLinkProgram(program);
    
    GLint status;
    glGetProgramiv (program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint infoLogLength;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
        
        GLchar *strInfoLog = new GLchar[infoLogLength + 1];
        glGetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);

        ostringstream out;
		out << "Pipeline link error: " << strInfoLog;
        delete[] strInfoLog;
		throw Exception(out.str());
    }
    
    for(int i = 0; i < shaders.size(); i++)
        glDetachShader(program, shaders[i]->handle);

    compiled = true;
}

Renderer* Program::createRenderer()
{
    return new Renderer(this);
}