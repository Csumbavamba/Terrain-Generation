#version 450 core

layout (location = 0) in vec4 vertex;

out vec4 particleColor;
out vec2 fragTexCoord;

uniform mat4 projection;
uniform vec2 offSet;
uniform vec4 color;

void main(void)
{
	float scale = 10.0f;
	particleColor = color;
	fragTexCoord = vertex.zw;

	gl_Position = projection * vec4((vertex.xy * scale) + offSet, 0.0f, 1.0f);
}