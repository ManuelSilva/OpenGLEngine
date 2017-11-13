#version 330 core

in vec3 exPosition;
in vec2 exTexcoord;
in vec3 exNormal;

out vec4 FragmentColor;

void main(void)
{
	//vec3 color = vec3(1.0);
	//vec3 color = (exPosition + vec3(1.0)) * 0.5;
	//vec3 color = vec3(exTexcoord, 0.0);
	vec3 color = (exNormal + vec3(1.0)) * 0.5;
	FragmentColor = vec4(color,1.0);
}
