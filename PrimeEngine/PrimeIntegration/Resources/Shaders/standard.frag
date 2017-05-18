#version 330 core

out vec4 color;

uniform vec2 lightPosition; //temp

in data
{
	vec4 position;
	vec4 color;
	vec2 texCord;
	float texture;
} fs_in;

uniform sampler2D textures[8];

 void main()
 {
	float lightIntesity = 1.0 / length(fs_in.position.xy - lightPosition) * 2;
	//color = fs_in.color * lightIntesity;
	if(fs_in.texture > 0.0)
	{
		int textureId = int(fs_in.texture - 0.5);
		vec4 textureColor = texture(textures[textureId], fs_in.texCord);
		if(textureColor.a < 0.1)
			discard;
		color = mix(textureColor, fs_in.color, fs_in.color.w);
	}
	else
	{
		color = fs_in.color;
	}
 }