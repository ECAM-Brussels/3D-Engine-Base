#include "SDL2Surface.h"

SDL2Surface::SDL2Surface()
{
	//Initialize SDL
	if( SDL_Init(SDL_INIT_VIDEO ) < 0)
	{
		ostringstream out;
		out << "SDL could not initialize! SDL Error: " << SDL_GetError();
		throw Exception(out.str());
	}
	
	//Use OpenGL 3.1 core
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	//Create window
	gWindow = SDL_CreateWindow("ECAM 3D Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
	if(gWindow == NULL )
	{
		ostringstream out;
		out << "Window could not be created! SDL Error: " << SDL_GetError();
		throw Exception(out.str());
	}
	
	//Create context
	gContext = SDL_GL_CreateContext(gWindow );
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

	stopped = false;
}

SDL2Surface::~SDL2Surface()
{
	//Destroy window	
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

void SDL2Surface::setApplication(Application* app)
{

}

bool SDL2Surface::isStopped()
{
	return stopped; 
}

void SDL2Surface::beginRender()
{
	//Event handler
	SDL_Event e;

	//Handle events on queue
	while(SDL_PollEvent( &e ) != 0)
	{
		//User requests quit
		if( e.type == SDL_QUIT )
		{
			stopped = true;
		}
	}

	//Clear color buffer
	glClear(GL_COLOR_BUFFER_BIT);
}

void SDL2Surface::endRender()
{
	//Update screen
	SDL_GL_SwapWindow(gWindow);
}

void SDL2Surface::setClearColor(GFloat red, GFloat green, GFloat blue, GFloat alpha)
{
	glClearColor(red, green, blue, alpha);
}


