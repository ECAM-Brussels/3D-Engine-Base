#version 430                                                                                              
in vec3 vertexPos;
in vec3 vertexNormal;
out vec3 frontColor;                                                                
uniform mat4 projectionMatrix;                                                                             
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform vec3 lightPosition;

void main() {

    mat3 normalMatrix;
	vec3 normal, lightDir;
    vec4 vertex;
	vec3 diffuse;
	float NdotL;

    normalMatrix = transpose(inverse(mat3(viewMatrix * modelMatrix)));

	normal = normalize(normalMatrix * vertexNormal);

    vertex = viewMatrix * modelMatrix * vec4( vertexPos.x, vertexPos.y, vertexPos.z, 1 );
	
	lightDir = normalize(mat3(viewMatrix) * lightPosition - vertexPos.xyz);
	
	NdotL = max(dot(normal, lightDir), 0.0);
    //NdotL = dot(normal, lightDir);

	diffuse = vec3(1.0, 1.0, 1.0);
	frontColor =  NdotL * diffuse;

	gl_Position = projectionMatrix * vertex;
}