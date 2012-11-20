#version 150

uniform mat4 modelview;

in vec4 position;
in vec3 normal;

out vec4 colour;

void main(void)
{
	vec3 light_direction = normalize(vec3(0.0, 0.0, 10.0) - vec3(position));
	vec3 E = normalize(-vec3(position));
	vec3 R = normalize(-reflect(light_direction, normal));

	vec4 ambient = vec4(0.0, 0.5, 0.5, 1.0);

	vec4 diffuse = vec4(0.0, 1.0, 1.0, 1.0) * max(dot(light_direction, normal), 0.0);
	diffuse = clamp(diffuse, 0.0, 1.0);

	vec4 specular = vec4(0.5, 1.0, 1.0, 1.0) * pow(max(dot(R, E), 0.0), 0.3);
	specular = clamp(specular, 0.0, 1.0);

	colour = ambient + diffuse + specular;
}
