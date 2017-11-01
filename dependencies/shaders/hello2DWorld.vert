#version 330 core

in vec4 in_Position;
in vec4 in_Color;

uniform mat4 Matrix;
uniform vec4 ColorStatic;


void main(void)
{
	gl_Position = Matrix * in_Position;
}