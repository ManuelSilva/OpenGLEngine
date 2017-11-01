#version 330 core

in vec4 in_Position;
in vec4 in_Color;

out vec4 ex_Color;

uniform mat4 Matrix;
uniform vec4 ColorStatic;

void main(void)
{
	
   gl_Position = Matrix * in_Position;
   ex_Color = normalize(in_Position) + ColorStatic;
}