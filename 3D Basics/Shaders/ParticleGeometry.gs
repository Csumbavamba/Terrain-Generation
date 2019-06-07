#version 450 core

layout (points) in; 
layout (triangle_strip, max_vertices = 4) out;

uniform mat4 PV; 
uniform vec3 quad1, quad2;

out GS_FS_VERTEX
{ 
	vec2 fragTexCoord; 
}	gs_out;

void main(void)
{
	float size = 0.1f;

	vec3 bottomLeft = gl_in[0].gl_Position.xyz + (-quad1-quad2) * size;
	gl_Position = PV * vec4(bottomLeft, 1.0f);
	gs_out.fragTexCoord = vec2(0.0f, 0.0f);
	EmitVertex();

	vec3 topLeft = gl_in[0].gl_Position.xyz + (-quad1 + quad2) * size;
	gl_Position = PV * vec4(topLeft, 1.0f);
	gs_out.fragTexCoord = vec2(0.0f, 1.0f);
	EmitVertex();

	vec3 bottomRight = gl_in[0].gl_Position.xyz + (quad1 - quad2) * size;
	gl_Position = PV * vec4(bottomRight, 1.0f);
	gs_out.fragTexCoord = vec2(1.0f, 0.0f);
	EmitVertex();

	vec3 topRight = gl_in[0].gl_Position.xyz + (quad1 + quad2) * size;
	gl_Position = PV * vec4(topRight, 1.0f);
	gs_out.fragTexCoord = vec2(1.0f, 1.0f);
	EmitVertex();

	EndPrimitive(); 
}
