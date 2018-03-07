#ifndef APPLICATION_H
#define APPLICATION_H

#include "ISurface.h"
#include "Renderer.h"
#include "Shader.h"
#include "VertexData.h"

class Application
{
protected:
    ISurface* surface;

public:
    Application(ISurface* surface);
    ~Application();
    int run();
    virtual void render() = 0;
    virtual void setup() = 0;
    virtual void teardown() = 0;
};

#endif