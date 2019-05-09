#version 450 core

in vec3 fragPos;
in vec3 fragNormal;
in vec2 fragTexCoord;

out vec4 color;

uniform sampler2D tex;
uniform float ambientStrength   = 0.20f;
uniform vec3 ambientColor       = vec3(1.0f, 1.0f, 1.0f);
uniform vec3 lightColor         = vec3(1.0f, 1.0f, 1.0f);
uniform vec3 lightPos           = vec3(-2.0f, 6.0f, 3.0f);

uniform vec3 camPos;// = vec3(0.0f, 0.0f, 2.0f);
uniform float lightSpecularStrength = 1.0f;
uniform float shininess = 32.0f;

uniform int rimExponent = 50;
uniform vec3 rimColor = vec3 (0.0f, 0.0f, 1.0f);


void main (void)
{
    // Ambient
    vec3 ambient = ambientStrength * ambientColor;

	//Light Direction
	vec3 normalizedLightDirection = normalize(fragNormal);
	vec3 lightDirection = normalize(fragPos - lightPos);

	//Diffuse Coloring
	float diffuseStrength = max(dot(normalizedLightDirection, -lightDirection ), 0.0f);
	vec3 diffuse = diffuseStrength * lightColor ;

	//Specular Highlight
	vec3 negViewDir = normalize(camPos - fragPos);

	//Blinn Phong Optimisation
	vec3 halfwayVec = normalize(-lightDirection + negViewDir);
	float spec = pow(max(dot(normalizedLightDirection, halfwayVec), 0.0f), shininess);
	vec3 specular = lightSpecularStrength * spec * lightColor;

	//Rim Lighting
	float rimFactor = 1.0 - dot(normalizedLightDirection, negViewDir);
	rimFactor = smoothstep(0.0, 1.0, rimFactor);
	rimFactor = pow(rimFactor, rimExponent);
	vec3 rim = rimFactor * rimColor * lightColor;

    color = vec4(ambient + diffuse + specular + rim, 1.0f) * (texture(tex, fragTexCoord));

}