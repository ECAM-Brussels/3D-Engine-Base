#ifndef GLUTSURFACE_H
#define GLUTSURFACE_H


#include "opengl.h"
#include <GL/glut.h>
#include <string>
#include <vector>
#include "vmath.h"
#include "Exception.h"
#include <sstream>
#include "ISurface.h"


using namespace std;
using namespace vmath;


class Application;

class GLUTSurface : public ISurface
{
public:
    static Application* app;
    GLUTSurface(int argc, char* argv[]);
    ~GLUTSurface();
    void setApplication(Application* app);
    bool isStopped();
    void beginRender();
    void endRender();

    void setClearColor(GFloat, GFloat, GFloat, GFloat);

private:
    static void appRenderWrapper();
    //Screen dimension constants
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;

    bool stopped;
};

#include "Application.h"

#endif