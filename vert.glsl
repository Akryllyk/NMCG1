#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 aColour;

uniform mat4 transform;

out vec3 colour;

void main()
{
    gl_Position = transform * vec4(position, 1.0f);
	colour = aColour;
} 