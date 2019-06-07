#version 450 core

in float lifeTime;
out vec4 color;

uniform sampler2D tex;

void main(void)
{
	vec4 colorValue = vec4 (0.8f, 0.5f, 0.0f, 1.0f);

	color = vec4(0.0f, 0.48f, 0.58f, lifeTime);
}