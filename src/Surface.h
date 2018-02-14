#ifndef SURFACE_H
#define SURFACE_H

#include "opengl.h"
#include <string>
#include <vector>
#include "vmath.h"
#include "Exception.h"
#include <sstream>

using namespace std;
using namespace vmath;

class Surface
{
public:
    Surface();
    ~Surface();
    bool isStopped();
    void beginRender();
    void endRender();

    void setClearColor(GFloat, GFloat, GFloat, GFloat);
    //void render(Pipeline *pipeline, VertexBuffer *vertexBuffer, IndexBuffer *indexBuffer);

private:
    //Screen dimension constants
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;

    //The window we'll be rendering to
    SDL_Window* gWindow = NULL;

    //OpenGL context
    SDL_GLContext gContext;

    bool stopped;
};

//TODO: Timing

#endif