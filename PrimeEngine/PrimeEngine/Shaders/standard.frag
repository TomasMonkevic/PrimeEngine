#version 330 core

out vec4 color;

in data
{
	vec4 position;
	vec4 color;
} fs_in;

 void main()
 {
	color = fs_in.color;
 }