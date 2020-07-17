	#version 330 core
/*
	precision highp float;

	in  vec3 ex_Color;
	out vec4 out_Color;

	void main(void)
	{
		out_Color = vec4(ex_Color,1.0);
	}
*/

	// Interpolated values from the vertex shaders
	in vec2 UV;

	// Ouput data
	out vec3 color;

	// Values that stay constant for the whole mesh.
	uniform sampler2D myTextureSampler;

	void main(){

		// Output color = color of the texture at the specified UV
		color = texture( myTextureSampler, UV ).rgb;
	}