#include "Application.h"

#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <iostream>

Application* theApp = NULL;
void appRenderWrapper()
{
    //Clear color buffer
	glClear(GL_COLOR_BUFFER_BIT);

    if(theApp) theApp->render();

    glutSwapBuffers();
    glutPostRedisplay();
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
        cerr<<"Error: "<<glewGetErrorString(err)<<endl;
    } else {
        if (GLEW_VERSION_4_3)
        {
            cout<<"Driver supports OpenGL 4.3\nDetails:"<<endl;
        }
    }

    cout << "GLUT App created" << endl;
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
    setup();
    glutMainLoop();
    teardown();
}

void Application::setClearColor(GFloat red, GFloat green, GFloat blue, GFloat alpha)
{
    glClearColor(red, green, blue, alpha);
}