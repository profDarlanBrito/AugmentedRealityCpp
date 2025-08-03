#version 460 core

in vec3 v_vertexColor; // Input vertex color	
in vec2 v_TexCoord; // Input texture coordinates

// The fragment shader outputs a solid red color to the fragment color output.
out vec4 fragColor;

uniform float u_offset; // Uniform variable for offset
uniform sampler2D uTexture; // Texture sampler

void main() {
	// Set the fragment color to a solid red
	//fragColor = vec4(v_vertexColor.r,v_vertexColor.g,v_vertexColor.b, 1.0);
	fragColor = texture(uTexture, v_TexCoord);
}