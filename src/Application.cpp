#include "Application.h"
#include "ISurface.h"
#include <iostream>

using namespace std;

Application::Application(ISurface* surface) 
{
    this->surface = surface;
    surface->setApplication(this);
}

Application::~Application()
{
    delete surface;
}

int Application::run()
{
    setup();

    while(!surface->isStopped())
    {
        surface->beginRender();
        render();
        surface->endRender();
    }

    teardown();

	return 0;
}