#ifndef PROGRAM_H
#define PROGRAM_H

#include "opengl.h"
#include <vector>

using namespace std;

class Renderer;
class Shader;

class Program
{
friend class Renderer;
private:
    bool compiled = false;
    GUInt program;
    vector<Shader*> shaders;

public:
    Program();
    ~Program();
    void addShader(Shader* shader);
    void compile();
    Renderer* createRenderer();
};

#include "Renderer.h"
#include "Shader.h"

#endif