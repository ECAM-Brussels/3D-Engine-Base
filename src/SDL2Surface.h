#ifndef SDL2SURFACE_H
#define SDL2SURFACE_H

#include "opengl.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <string>
#include <vector>
#include "vmath.h"
#include "Exception.h"
#include <sstream>
#include "ISurface.h"

using namespace std;
using namespace vmath;

class SDL2Surface : public ISurface
{
public:
    SDL2Surface();
    ~SDL2Surface();
    void setApplication(Application* app);
    bool isStopped();
    void beginRender();
    void endRender();

    void setClearColor(GFloat, GFloat, GFloat, GFloat);

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