#version 450 core

layout (location = 0) in vec4 position;

out float lifeTime;

void main(void)
{
	gl_Position = vec4(position.xyz, 1.0f);
	lifeTime = position.w;
}