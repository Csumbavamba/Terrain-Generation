#version 450 core

in GS_FS_VERTEX
{
	vec2 fragTexCoord;
} fs_in;

uniform sampler2D tex;

out vec4 color;

void main(void)
{
	vec4 colorValue = vec4 (123.0f/255.0f, 173.0f/255.0f, 203.0f/255.0f, 1.0f);

	color = (texture(tex, vec2(fs_in.fragTexCoord.x, fs_in.fragTexCoord.y)) * colorValue);
}