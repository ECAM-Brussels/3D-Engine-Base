#version 430                                                                                              
in vec3 vertex;                                                                    
uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;
void main()
{
    gl_Position = projectionMatrix * modelViewMatrix * vec4( vertex.x, vertex.y, vertex.z, 1 );
}