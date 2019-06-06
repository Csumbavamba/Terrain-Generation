#version 450 core

in vec2 fragTexCoord;

out vec4 color;

uniform sampler2D tex;

void main (void)
{
    color = vec4(vec3(1.0 - texture(tex, fragTexCoord)), 1.0);
}