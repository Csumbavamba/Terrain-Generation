#version 450 core

in vec2 fragTexCoord;

out vec4 color;
in float lifeTime;
uniform sampler2D tex;

void main (void)
{
    color = texture(tex, fragTexCoord);


}