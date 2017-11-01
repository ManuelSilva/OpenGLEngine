#version 330 core

in vec4 ex_Color;
out vec4 out_Color;

uniform mat4 Matrix;
uniform vec4 ColorStatic;

void main(void)
{
	out_Color = ex_Color;
}