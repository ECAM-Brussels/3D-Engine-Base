#include "Application.h"

#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <iostream>
#include <sstream>

Application* theApp = NULL;

void appUpdateWrapper(int timerID)
{
    glutTimerFunc(Application::FRAME_LENGTH, appUpdateWrapper, 0);
    int time = glutGet(GLUT_ELAPSED_TIME); 
    if(theApp) theApp->update(time);
    glutPostRedisplay();
}

void appRenderWrapper()
{
	glClear(GL_COLOR_BUFFER_BIT);
    if(theApp) theApp->render();
    glutSwapBuffers();
}

Application::Application(int argc, char* argv[]) 
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitContextVersion (4, 3);
    glutInitContextFlags (GLUT_CORE_PROFILE | GLUT_DEBUG);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutCreateWindow("ECAM 3D Engine");
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (GLEW_OK != err)	{
        ostringstream out;
		out <<"Error: "<<glewGetErrorString(err)<<endl;
		throw Exception(out.str());
    }
    glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
}

Application::~Application()
{
    theApp = NULL;
    cout << "GLUT App destroyed" << endl;
}

int Application::run()
{
    theApp = this;
    glutDisplayFunc(appRenderWrapper);
    glutTimerFunc(FRAME_LENGTH, appUpdateWrapper, 0);
    setup();
    glutMainLoop();
    teardown();
}

void Application::setClearColor(GFloat red, GFloat green, GFloat blue, GFloat alpha)
{
    glClearColor(red, green, blue, alpha);
}