#include "GLUTSurface.h"
#include <iostream>

Application* GLUTSurface::app = NULL;

GLUTSurface::GLUTSurface(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("ECAM 3D Engine");
}

GLUTSurface::~GLUTSurface()
{

}

void GLUTSurface::setApplication(Application* app)
{
    cout << "hello" << endl;
    GLUTSurface::app = app;
    cout << "hello2" << endl;
    glutDisplayFunc(appRenderWrapper);
    cout << "hello3" << endl;
}

bool GLUTSurface::isStopped()
{
    cout << "hello4" << endl;
    glutMainLoop();
    cout << "hello5" << endl;
    return true;
}

void GLUTSurface::beginRender()
{

}

void GLUTSurface::endRender()
{

}

void GLUTSurface::setClearColor(GFloat red, GFloat green, GFloat blue, GFloat alpha)
{
    glClearColor(red, green, blue, alpha);
}

void GLUTSurface::appRenderWrapper()
{
    app->render();
}
