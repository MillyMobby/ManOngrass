#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture samplers
uniform sampler2D tex1;


void main()
{
	vec4 texColor = texture(tex1, TexCoord);
	if(texColor.a < 0.3) discard;
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	FragColor = texColor;
}