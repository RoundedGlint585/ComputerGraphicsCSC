#version 330 core
layout (location = 0) in vec3 pos;
out vec2 coord;
void main()
{
    gl_Position = vec4(pos.xyz, 1.0);
    coord = pos.xy;
}
