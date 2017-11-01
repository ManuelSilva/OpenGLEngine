#version 330 core

out vec4 out_Color;

uniform mat4 Matrix;
uniform vec4 ColorStatic;

void main(void)
{
	out_Color = ColorStatic;
}