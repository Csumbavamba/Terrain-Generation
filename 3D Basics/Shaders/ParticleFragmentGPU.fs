#version 450 core


out vec4 color;

in float lifeTime;

void main(void)
{
	vec4 colorValue = vec4 (0.0f, 0.5f, 1.0f, 1.0f);

	color = vec4(colorValue.xyz, lifeTime);
}