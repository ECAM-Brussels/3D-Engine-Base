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
    static const int SCREEN_WIDTH = 640;
    static const int SCREEN_HEIGHT = 480;
    static const int FRAME_LENGTH = 1000/60;


    Application(int argc, char* argv[]);
    virtual ~Application();
    int run();
    void setClearColor(GFloat red, GFloat green, GFloat blue, GFloat alpha);
    virtual void update(int elapsedTime) = 0;
    virtual void render() = 0;
    virtual void setup() = 0;
    virtual void teardown() = 0;
};

#endif