#include "Application.h"
#include <iostream>

using namespace std;

class MyApplication: public Application
{
private:
    Renderer *renderer = NULL;
    VertexData *inputs = NULL;
    float angle = 0;
    
public:
    void render();
    void setup();
    void teardown();
};

void MyApplication::render()
{
    angle = angle + 1.0f;
    mat4 modelViewMatrix = rotate(angle, 0.0f, 1.0f, 0.0f);
    renderer->setModelViewMatrix(modelViewMatrix);
    renderer->render();
}

void MyApplication::setup()
{
    string vertexSrc = 
        "#version 430                                                                                                      \n"
        "layout (location = 0) in vec3 VertexPos3D;                                                                        \n"
        "uniform mat4 projectionMatrix;                                                                                    \n"
        "uniform mat4 modelViewMatrix;                                                                                     \n"
        "void main()                                                                                                       \n"
        "{                                                                                                                 \n"
        "    gl_Position = projectionMatrix * modelViewMatrix * vec4( VertexPos3D.x, VertexPos3D.y, VertexPos3D.z, 1 );    \n"
        "}                                                                                                                   ";

    Shader vShader(vertexSrc, SHADER_VERTEX);

    string pixelSrc = 
        "#version 430                                  \n"
        "out vec4 Fragment;                            \n"
        "void main()                                   \n"
        "{                                             \n"
        "    Fragment = vec4( 1.0, 1.0, 1.0, 1.0 );    \n"
        "}                                               ";

    Shader pShader(pixelSrc, SHADER_PIXEL);
    vector<Shader*> shaders;
    shaders.push_back(&vShader);
    shaders.push_back(&pShader);
    renderer = new Renderer(shaders);

    mat4 projectionMatrix = perspective(1.0f, 640.0f/480, 1.0f, 100.0f);
    mat4 lookatMatrix = lookat(vec3(50, 50, 50), vec3(0, 0, 0), vec3(0, 1, 0));
    projectionMatrix = projectionMatrix * lookatMatrix;

    mat4 modelViewMatrix = rotate(angle, 0.0f, 1.0f, 0.0f); 
    renderer->setProjectionMatrix(projectionMatrix);
    renderer->setModelViewMatrix(modelViewMatrix);

    //IBO data
	GLuint indexData[] = { 0, 1, 2, 0, 2, 3 };
    //indexBuffer = new Renderer::IndexBuffer(indexData, 4);

    //VBO data
    vec3 vertexData[] =
    {
        vec3(-0.5f, -0.5f, 0.0f),
        vec3(0.5f, -0.5f, 0.0f),
        vec3(0.5f,  0.5f, 0.0f),
        vec3(-0.5f,  0.5f, 0.0f)
    };
    //vertexBuffer = new Renderer::VertexBuffer(vertexData, 4);

    inputs = new VertexData();
    inputs->put(0, vertexData, 4);
    inputs->index(indexData, 6);
    inputs->pack();

    renderer->setVertexData(*inputs);

    surface.setClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void MyApplication::teardown()
{
    delete renderer;
    delete inputs;
}

int main( int argc, char* args[] )
{
    try 
    {
        MyApplication app = MyApplication();
	    return app.run();
    }
	catch(Exception e)
    {
        cout << e.getMessage() << endl;
        return 1;
    }
}