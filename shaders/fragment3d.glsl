#version 400

in vec2 uv_cords;
in vec3 surface_normal;

uniform sampler2D mysampler;

out vec4 color;

void main()
{
    //gl_FragColor = vec4(1.0 * surface_normal.z, 1.0 * uv_cords.x, 1.0 * surface_normal.y, 1.0);
    color = texture(mysampler, uv_cords).rgba;
}