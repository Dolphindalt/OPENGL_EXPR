#version 400

layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec2 passing_uv_cords;
layout (location = 2) in vec3 passing_surface_normal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec2 uv_cords;
out vec3 surface_normal;

void main()
{
    gl_Position = projection * view * model * vec4(vertex_position.xyz, 1);
    uv_cords = vec2(passing_uv_cords.x, -passing_uv_cords.y);
    surface_normal = passing_surface_normal;
}