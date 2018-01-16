#version 400

in vec3 vertex_position;

uniform mat4 MVP;
uniform mat4 model;

out vec3 stuff;

void main()
{
    gl_Position = MVP * vec4(vertex_position.xyz, 1);
    stuff = vertex_position;
}