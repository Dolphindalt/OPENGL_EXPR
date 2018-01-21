#version 400

layout (location = 0) in vec3 vertex_position;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec3 stuff;

void main()
{
    gl_Position = projection * view * model * vec4(vertex_position.xyz, 1);
    stuff = vertex_position;
}