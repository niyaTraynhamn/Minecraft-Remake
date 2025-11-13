#version 330 core

in vec3 crntPos; // Imports the current position from the Vertex Shader
in vec3 Normal; // Imports the normal from the Vertex Shader
in vec2 texCoord; // Inputs the texture coordinates from the Vertex Shader
in vec3 color; // Inputs the color from the Vertex Shader

out vec4 FragColor; // Outputs colors in RGBA

uniform sampler2D tex0; // Gets the Texture Unit from the main function
uniform sampler2D texSide;
uniform sampler2D texTop;
uniform bool uUseTint;
uniform vec3 uTintColor;


void main()
{
	vec4 base = texture(tex0, texCoord);
	if (uUseTint) {
		base.rgb *= uTintColor;  // grass tint via uniform
	}
	FragColor = base; // If you want per-vertex color too: base.rgb *= color;
}
