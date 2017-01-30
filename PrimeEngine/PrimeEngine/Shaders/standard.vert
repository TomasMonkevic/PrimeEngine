#version 330 core

layout (location = 0) in vec4 position;

uniform mat4 pr_matrix;
uniform mat4 model_matrix = mat4(1.0f);

void main()
{
	gl_Position = pr_matrix * model_matrix * position;
}