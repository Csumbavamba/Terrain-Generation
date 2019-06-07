#version 450 core

in GS_FS_VERTEX
{
	vec2 fragTexCoord;
} fs_in;

uniform sampler2D tex;

out vec4 color;

void main(void)
{
	vec4 colorValue = vec4 (0.8f, 0.5f, 0.0f, 1.0f);

	color = (texture(tex, vec2(fs_in.fragTexCoord.x, fs_in.fragTexCoord.y)) * colorValue);
}