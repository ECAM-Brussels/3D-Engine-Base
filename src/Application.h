#ifndef APPLICATION_H
#define APPLICATION_H

#include "opengl.h"
#include "Shader.h"
#include "VertexData.h"
#include "Renderer.h"
#include "Exception.h"

class Application
{
public:
    //Screen dimension constants
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;


    Application(int argc, char* argv[]);
    virtual ~Application();
    int run();
    void setClearColor(GFloat red, GFloat green, GFloat blue, GFloat alpha);
    virtual void render() = 0;
    virtual void setup() = 0;
    virtual void teardown() = 0;
};

#endif