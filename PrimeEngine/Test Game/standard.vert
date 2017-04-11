#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 textureCord;

uniform mat4 pr_matrix;
uniform mat4 view_matrix = mat4(1.0f);
uniform mat4 model_matrix = mat4(1.0f);

out data
{
	vec4 position;
	vec4 color; //only color needed
	vec2 texCord;
} vs_out;

void main()
{
	gl_Position = pr_matrix * view_matrix * model_matrix * position;
	vs_out.position = model_matrix * position;
	vs_out.color = color;
	vs_out.texCord = textureCord;
}