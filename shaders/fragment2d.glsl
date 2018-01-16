#version 400

in vec3 stuff;

void main()
{
    gl_FragColor = vec4(stuff.x, stuff.y, stuff.z, 1.0);
}