#ifndef ISURFACE_H
#define ISURFACE_H

#include "opengl.h"

class Application;

class ISurface
{
public:
    virtual void setApplication(Application* app) = 0;
    virtual bool isStopped() = 0;
    virtual void beginRender() = 0;
    virtual void endRender() = 0;
    virtual void setClearColor(GFloat, GFloat, GFloat, GFloat) = 0;
};

#include "Application.h"

#endif