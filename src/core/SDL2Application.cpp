#include "Application.h"

#include <GL/glew.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <iostream>
#include <sstream>

using namespace std;

//The window we'll be rendering to
SDL_Window* gWindow = NULL; 

Application::Application(int argc, char* argv[]) 
{
    //Initialize SDL
	if( SDL_Init(SDL_INIT_VIDEO ) < 0)
	{
		ostringstream out;
		out << "SDL could not initialize! SDL Error: " << SDL_GetError();
		throw Exception(out.str());
	}
	
	//Use OpenGL 4.3 core
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 24 );
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

	//Create window
	gWindow = SDL_CreateWindow("ECAM 3D Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
	if(gWindow == NULL )
	{
		ostringstream out;
		out << "Window could not be created! SDL Error: " << SDL_GetError();
		throw Exception(out.str());
	}
	
	//Create context
	SDL_GLContext gContext = SDL_GL_CreateContext(gWindow );
	if(gContext == NULL)
	{
		ostringstream out;
		out << "OpenGL context could not be created! SDL Error: " << SDL_GetError();
		throw Exception(out.str());
	}
	
	//Initialize GLEW
	glewExperimental = GL_TRUE; 
	GLenum glewError = glewInit();
	if(glewError != GLEW_OK)
	{
		ostringstream out;
		out << "Error initializing GLEW! " << glewGetErrorString(glewError);
		throw Exception(out.str());
	}

	//Use Vsync
	if(SDL_GL_SetSwapInterval( 1 ) < 0)
	{
		ostringstream out;
		out << "Warning: Unable to set VSync! SDL Error: " << SDL_GetError();
		throw Exception(out.str());
	}

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glDepthRange(0.0, 1.0);

	glPointSize(5);
}

Application::~Application()
{
    //Destroy window	
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

int Application::run()
{
    setup();

    bool running = true;
    while(running)
    {
        //Event handler
        SDL_Event e;

        //Handle events on queue
        while(SDL_PollEvent( &e ) != 0)
        {
            //User requests quit
            if( e.type == SDL_QUIT )
            {
                running = false;
            }
        }

        //Clear color buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
		int elapsedTime = SDL_GetTicks();
		update(elapsedTime);
        render();
        
        //Update screen
	    SDL_GL_SwapWindow(gWindow);
    }

    teardown();

	return 0;
}

void Application::setClearColor(GFloat red, GFloat green, GFloat blue, GFloat alpha)
{
	glClearColor(red, green, blue, alpha);
	glClearDepth(1.0f);
}