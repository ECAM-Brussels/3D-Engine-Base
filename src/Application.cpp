#include "Application.h"
#include "Surface.h"
#include <iostream>

using namespace std;

int Application::run()
{
    setup();

    while(!surface.isStopped())
    {
        surface.beginRender();
        render();
        surface.endRender();
    }

    teardown();

	return 0;
}