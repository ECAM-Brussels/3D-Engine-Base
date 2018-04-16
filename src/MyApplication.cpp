#include "core/Application.h"
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
    Buffer* vertex = NULL;
    Buffer* normal = NULL;
    Buffer* index = NULL;
    
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
    angle = 45.0f / 1000 * elapsedTime;
    mat4 modelMatrix = rotate(angle, 0.0f, 1.0f, 0.0f);
    renderer->setMatrix("modelMatrix", modelMatrix);
}

void MyApplication::render()
{
    renderer->indexedRender(PRIMITIVE_TRIANGLES, dragon->getIndexCount()); 
}

void MyApplication::setup()
{
     
    program = new Program(); 
    program->addShader(Shader::fromFile("shaders/diffuse.vert"));
    program->addShader(Shader::fromFile("shaders/diffuse.frag"));
    program->link();

    renderer = program->createRenderer();

    mat4 projectionMatrix = perspective(30.0f, 640.0f/480, 0.001f, 100.0f);

    mat4 viewMatrix = lookat(vec3(15, 15, 15), vec3(0, 4, 0), vec3(0, 1, 0));
    mat4 modelMatrix = rotate(angle, 0.0f, 1.0f, 0.0f);
    renderer->setMatrix("projectionMatrix", projectionMatrix);
    renderer->setMatrix("modelMatrix", modelMatrix);
    renderer->setMatrix("viewMatrix", viewMatrix);
    renderer->setVec("lightPosition", vec3(1000, 1000, -1000));

    dragon = Mesh::fromOBJ("models/dragon.obj");

     

    //vertex = new Buffer(dragon->getVertexCount(), 3, FLOAT, dragon->getVertex());
    //normal = new Buffer(dragon->getVertexCount(), 3, FLOAT, dragon->getNormal());
    //index = new Buffer(dragon->getIndexCount(), 1, UINT, dragon->getIndex());

     

    renderer->setVertexData("vertexPos", dragon->getVertex(), TYPE_FLOAT, 0, 3, sizeof(VertexData));
    renderer->setVertexData("vertexNormal", dragon->getVertex(), TYPE_FLOAT, sizeof(vec3), 3, sizeof(VertexData));
    renderer->index(dragon->getIndex());
    
    setClearColor(0.95f, 0.95f, 0.95f, 1.0f); 
     
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