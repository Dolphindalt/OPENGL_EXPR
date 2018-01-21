#version 400

in vec2 uv_cords;

uniform sampler2D mysampler;

out vec4 color;

void main()
{
    color = texture(mysampler, uv_cords).rgba;
}