#include "core/Application.h"
#include <iostream>


using namespace std;

struct Particule
{
    vec4 position;
    vec4 velocity;
    Particule(vec3 pos, vec3 vel)
    {
        position = vec4(pos[0], pos[1], pos[2], 1.0f);
        velocity = vec4(vel[0], vel[1], vel[2], 1.0f);
    }
};

class Simulator: public Application
{
private:
    Program* program = NULL;
    Program* compute = NULL;
    Renderer* renderer = NULL;
    Computer* computer = NULL;
    Buffer* particules = NULL;
    Buffer* velocities = NULL;
    
public:
    Simulator(int argc, char* argv[]);
    void update(int time);
    void render();
    void setup();
    void teardown();
};

Simulator::Simulator(int argc, char* argv[]) : Application(argc, argv) {}

void Simulator::update(int elapsedTime)
{
    computer->compute(1, 1, 1);
}

void Simulator::render()
{
     renderer->render(PRIMITIVE_POINTS, 4);
}

void Simulator::setup()
{   
    setClearColor(0.95f, 0.95f, 0.95f, 1.0f); 

    Particule pp[] = {
        Particule(vec3(1, 10, 1), vec3(0)),
        Particule(vec3(-1, 10, 1), vec3(0)),
        Particule(vec3(1, 10, -1), vec3(0)),
        Particule(vec3(-1, 10, -1), vec3(0))
    };

    /*vec3 parti[] = {
        vec3(1, 10, 1),
        vec3(-1, 10, 1),
        vec3(1, 10, -1),
        vec3(-1, 10, -1)
    };*/

    particules = new Buffer(pp, sizeof(pp));

    /*vec3 veloc[] = {
        vec3(0),
        vec3(0),
        vec3(0),
        vec3(0)
    };

    velocities = new Buffer(4, 3, FLOAT, veloc);*/

    program = new Program();
    program->addShader(Shader::fromFile("shaders/perspective.vert"));
    program->addShader(Shader::fromFile("shaders/black.frag"));
    program->link();

    renderer = program->createRenderer();

    renderer->setVertexData("vertex", particules, TYPE_FLOAT, 0, 3, sizeof(Particule));

    mat4 projection = perspective(90.0f, 640.0/480.0, 0.1, 20);
    mat4 view = lookat(vec3(0, 5, -10), vec3(0, 5, 0), vec3(0, 1, 0));

    renderer->setMatrix("projectionMatrix", projection);
    renderer->setMatrix("modelViewMatrix", view);

    compute = new Program();
    compute->addShader(Shader::fromFile("shaders/gravity.comp"));
    compute->link();

    computer = compute->createComputer();
    computer->setData(1, particules);
    //computer->setData(2, velocities);
}

void Simulator::teardown()
{
   
}

int main(int argc, char** argv)
{
    try 
    {
        Simulator app = Simulator(argc, argv); 
	    return app.run();
    }
	catch(Exception e)
    {
        cout << e.getMessage() << endl;
        return 1;
    }
}