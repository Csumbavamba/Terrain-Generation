#version 450 core

in vec3 fragPos;
in vec3 fragNormal;
in vec2 fragTexCoord;

out vec4 color;

uniform sampler2D tex;
uniform vec3 camPos;
uniform samplerCube skybox;

void main (void)
{
	//Light Direction
	vec3 normalizedLightDirection = normalize(fragNormal);
	vec3 lightDirection = normalize(fragPos - camPos);
	//Reflection
	vec3 reflectDir = reflect(lightDirection, normalizedLightDirection);

	//Reflective
	color = vec4(texture(skybox, reflectDir ).rgb, 1.0f);
}