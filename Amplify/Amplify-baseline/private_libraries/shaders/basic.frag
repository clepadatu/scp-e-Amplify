#version 330 core

layout (location = 0) out vec4 color;

uniform vec4 palette;
uniform vec2 light_position;

in vec4 v_position;
in DATA
{
vec4 position;
vec4 color;
} fs_in;
void main()
{
float intensity=1.0 / length(fs_in.position.xy-light_position);
//color = palette * intensity;
//vec4(1.0, 0.0, 1.0, 1.0);
color=fs_in.color*intensity;
}