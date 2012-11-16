#version 150

uniform mat4 modelview, projection;

in vec3 position;

void main(void)
{
	gl_Position = projection * modelview * vec4(position, 1.0);
}
