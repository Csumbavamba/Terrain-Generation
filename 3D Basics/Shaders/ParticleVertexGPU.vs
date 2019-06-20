#version 450 core

layout (location = 0) in vec4 position;

out float lifeTime;

uniform mat4 PVM;

void main(void)
{
	gl_Position = PVM * vec4(position.xyz, 1.0f);
	lifeTime = position.w;
}