#version 150

uniform sampler2D s;

in vec4 position;

out vec4 colour;

void main(void)
{
	colour = clamp(texture(s, vec2((position + 1) / 2)) + vec4(1.0, 0.0, 0.0, 1.0), 0.0, 1.0);
	//colour = vec4(1.0, 0.0, 0.0, 1.0);
	//colour = vec4(vec2((position + 1) / 2), 0.0, 1.0);
}
