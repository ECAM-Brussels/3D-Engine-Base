#ifndef PROGRAM_H
#define PROGRAM_H

#include "opengl.h"
#include <vector>

using namespace std;

class Renderer;
class Shader;
class Computer;

class Program
{
private:
    bool linked = false;
    GUInt program;
    vector<Shader*> shaders;

public:
    Program();
    ~Program();
    void addShader(Shader* shader);
    void link();
    Renderer* createRenderer();
    Computer* createComputer();
    GUInt getName();
};

#include "Renderer.h"
#include "Shader.h"
#include "Computer.h"

#endif