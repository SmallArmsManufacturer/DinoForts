#version 150

uniform mat4 modelview, projection;
uniform mat3 normalmatrix;

in vec3 in_Position, in_Normal;

out vec4 position;
out vec3 normal;

void main(void)
{
	position = modelview * vec4(in_Position, 1.0);
	gl_Position = projection * position;
	normal = normalize(normalmatrix * in_Normal);
}
