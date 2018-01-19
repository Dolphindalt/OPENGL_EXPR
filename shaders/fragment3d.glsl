#version 400

in vec2 uv_cords;
in vec3 surface_normal;

void main()
{
    gl_FragColor = vec4(surface_normal.y * 1.0, 1.0, uv_cords.x * 1.0, 1.0);
}