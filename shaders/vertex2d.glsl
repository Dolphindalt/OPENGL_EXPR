#version 400

layout (location = 0) in vec3 vertex_position;

uniform mat4 MVP;
uniform mat4 model;

out vec3 stuff;

void main()
{
    gl_Position = MVP * model * vec4(vertex_position.xyz, 1);
    stuff = vertex_position;
}