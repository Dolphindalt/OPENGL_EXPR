#version 400

in vec2 uv_cords;
in vec3 surface_normal;

void main()
{
    gl_FragColor = vec4(1.0 * surface_normal.x, 1.0, 1.0, 1.0);
}