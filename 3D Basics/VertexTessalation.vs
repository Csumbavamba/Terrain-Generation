#version 450 core

in vec3 position;

uniform mat4 PVM;

void main(void)
{
	gl_Position = PVM * vec4(position, 1.0f);
}