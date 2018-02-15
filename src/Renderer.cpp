#include "Renderer.h"
#include "Exception.h"
#include <sstream>

Renderer::Renderer(vector<Shader*> &shaders)
{
    handle = glCreateProgram();
    
    for(int i = 0; i < shaders.size(); i++)
    	glAttachShader(handle, shaders[i]->handle);
    
    glLinkProgram(handle);
    
    GLint status;
    glGetProgramiv (handle, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint infoLogLength;
        glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &infoLogLength);
        
        GLchar *strInfoLog = new GLchar[infoLogLength + 1];
        glGetProgramInfoLog(handle, infoLogLength, NULL, strInfoLog);

        ostringstream out;
		out << "Pipeline link error: " << strInfoLog;
        delete[] strInfoLog;
		throw Exception(out.str());
    }
    
    for(int i = 0; i < shaders.size(); i++)
        glDetachShader(handle, shaders[i]->handle);
}

Renderer::~Renderer()
{
    glDeleteProgram(handle);
}

void Renderer::render(VertexData &inputs)
{
    glUseProgram(handle);

    glBindVertexArray(inputs.handle);
    glDrawElements(GL_TRIANGLES, inputs.length, GL_UNSIGNED_INT, NULL);
    glBindVertexArray(0);

    glUseProgram(0);
}