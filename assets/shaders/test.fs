#version 150

uniform mat4 modelview, projection, normalmatrix;

in vec3 normal;

out vec4 colour;

void main(void)
{
	vec3 lightpos = vec3(modelview * vec4(2.0, 2.0, 2.0, 0.0));
	vec3 lightdir = normalize(lightpos - vec3(gl_FragCoord));
	float diffuseFactor = max(0.0, dot(normal, lightdir));
	colour = diffuseFactor * vec4(1.0, 0.0, 0.0, 1.0);
}
