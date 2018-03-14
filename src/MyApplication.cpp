#include "Application.h"
#include "Mesh.h"
#include <iostream>


using namespace std;

class MyApplication: public Application
{
private:
    Program* program = NULL;
    Renderer *renderer = NULL;
    float angle = 0;
    Mesh* dragon = NULL;
    
public:
    MyApplication(int argc, char* argv[]);
    void update(int time);
    void render();
    void setup();
    void teardown();
};

MyApplication::MyApplication(int argc, char* argv[]) : Application(argc, argv) {}

void MyApplication::update(int elapsedTime)
{
    angle = 180.0f / 1000 * elapsedTime;
    mat4 modelViewMatrix = rotate(angle, 0.0f, 1.0f, 0.0f);
    renderer->setMatrix("modelViewMatrix", modelViewMatrix);
}

void MyApplication::render()
{
    renderer->render();   
}

void MyApplication::setup()
{   
    program = new Program(); 
    program->addShader(Shader::fromFile("shaders/perspective.vert"));
    program->addShader(Shader::fromFile("shaders/white.frag"));
    program->compile();

    renderer = program->createRenderer();

    mat4 projectionMatrix = perspective(1.0f, 640.0f/480, 1.0f, 1000.0f);
    mat4 lookatMatrix = lookat(vec3(500, 500, 500), vec3(0, 3, 0), vec3(0, 1, 0));
    projectionMatrix = projectionMatrix * lookatMatrix;

    mat4 modelViewMatrix = rotate(angle, 0.0f, 1.0f, 0.0f); 
    renderer->setMatrix("projectionMatrix", projectionMatrix);
    renderer->setMatrix("modelViewMatrix", modelViewMatrix);

    dragon = Mesh::fromOBJ("models/dragon.obj");

    renderer->put("VertexPos3D", dragon->getVertex(), dragon->getVertexCount());
    renderer->index(dragon->getIndex(), dragon->getIndexCount());
    
    setClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
}

void MyApplication::teardown()
{
    delete renderer;
    delete program;
}

int main(int argc, char** argv)
{
    try 
    {
        MyApplication app = MyApplication(argc, argv); 
	    return app.run();
    }
	catch(Exception e)
    {
        cout << e.getMessage() << endl;
        return 1;
    }
}