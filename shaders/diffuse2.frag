#version 430 
in vec3 normal;
in vec3 lightPos;
in vec4 vertex;
out vec3 Fragment;
void main()
{
    vec3 diffuse;
	float NdotL;
    vec3 lightDir;
    vec3 normalN;

    lightDir = normalize(lightPos - vertex.xyz);
    normalN = normalize(normal);

    NdotL = max(dot(normalN, lightDir), 0.0);

	diffuse = vec3(1.0, 1.0, 1.0);
	Fragment =  NdotL * diffuse;
}