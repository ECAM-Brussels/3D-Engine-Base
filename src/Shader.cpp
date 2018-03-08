#include "Shader.h"
#include "Exception.h"
#include <sstream>
#include <iostream>

Shader::Shader(string src, ShaderType type)
{
    
    handle = glCreateShader(type);
    cout << "createShader" << endl;
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