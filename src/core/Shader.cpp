#include "Shader.h"
#include "Exception.h"
#include <sstream>
#include <iostream>
#include <fstream>

Shader::Shader(string src, ShaderType type)
{
    
    handle = glCreateShader(type);
    const char *strData = src.c_str();
    glShaderSource(handle, 1, &strData, NULL);
    
    glCompileShader(handle);
    
    GLint status;
    glGetShaderiv(handle, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint infoLogLength;
        glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &infoLogLength);
        
        GLchar *strInfoLog = new GLchar[infoLogLength + 1];
        glGetShaderInfoLog(handle, infoLogLength, NULL, strInfoLog);
        
        ostringstream out;
		out << "Shader complile error: " << strInfoLog;
        delete[] strInfoLog;
		throw Exception(out.str());
    }
}

Shader::~Shader()
{
    glDeleteShader(handle);
}

Shader* Shader::fromFile(string path)
{
    size_t point = path.find_last_of('.');
    string extension = path.substr(point+1, string::npos);
    ShaderType type = SHADER_VERTEX;
    if(extension.compare("frag") == 0)
        type = SHADER_PIXEL;
    if(extension.compare("comp") == 0)
        type = SHADER_COMPUTE;

    ifstream in(path);
    stringstream buffer;
    buffer << in.rdbuf();

    return new Shader(buffer.str(), type);
}