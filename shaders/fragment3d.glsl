#version 400

in vec2 uv_cords;
in vec3 surface_normal;

uniform sampler2D sampler;

void main()
{
    //gl_FragColor = vec4(1.0 * surface_normal.z, 1.0 * uv_cords.x, 1.0 * surface_normal.y, 1.0);
    vec4 textureColor = texture(sampler, uv_cords);
    gl_FragColor = textureColor;
}