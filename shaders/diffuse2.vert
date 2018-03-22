#version 430                                                                                              
in vec3 vertexPos;
in vec3 vertexNormal;                                                                
uniform mat4 projectionMatrix;                                                                             
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform vec3 lightPosition;

out vec3 normal;
out vec3 lightPos;
out vec4 vertex;

void main() {

    mat3 normalMatrix;
	vec3 diffuse;
	float NdotL;

    normalMatrix = transpose(inverse(mat3(viewMatrix * modelMatrix)));

	normal = normalize(normalMatrix * vertexNormal);
	
	lightPos = mat3(viewMatrix) * lightPosition;

    vertex = viewMatrix * modelMatrix * vec4( vertexPos.x, vertexPos.y, vertexPos.z, 1 );

	gl_Position = projectionMatrix * vertex;
}