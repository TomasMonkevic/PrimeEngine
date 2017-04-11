#version 330 core

out vec4 color;

uniform vec2 lightPosition; //temp

in data
{
	vec4 position;
	vec4 color;
	vec2 texCord;
} fs_in;

uniform sampler2D outTexture;

 void main()
 {
	float lightIntesity = 1.0 / length(fs_in.position.xy - lightPosition) * 2;
	//color = fs_in.color * lightIntesity;
	color = texture(outTexture, fs_in.texCord);
 }