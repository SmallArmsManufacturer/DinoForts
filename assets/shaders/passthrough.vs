#version 150

in vec3 in_Position;

out vec4 position;

void main(void)
{
	position = vec4(in_Position, 1.0);
	gl_Position = position;
}
