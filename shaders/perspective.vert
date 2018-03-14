#version 430                                                                                              
in vec3 VertexPos3D;                                                                    
uniform mat4 projectionMatrix;                                                                             
uniform mat4 modelViewMatrix;                                                                               
void main()                                                                                                     
{                                                                                                            
    gl_Position = projectionMatrix * modelViewMatrix * vec4( VertexPos3D.x, VertexPos3D.y, VertexPos3D.z, 1 );
}