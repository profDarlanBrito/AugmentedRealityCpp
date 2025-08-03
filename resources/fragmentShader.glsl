#version 460 core

in vec3 v_vertexColor; // Input vertex color	
in vec2 v_TexCoord; // Input texture coordinates
in vec3 v_Normal; // Input normal vector

// The fragment shader outputs a solid red color to the fragment color output.
out vec4 fragColor;

uniform float u_offset; // Uniform variable for offset
uniform sampler2D uTexture; // Texture sampler
uniform int uLoadTexture; // Uniform variable to control texture loading

void main() {
	// Set the fragment color to a solid red
	// If uLoadTexture is 0, use the vertex color; otherwise, use the texture
	if (uLoadTexture == 0)
		fragColor = vec4(v_vertexColor.r, v_vertexColor.g, v_vertexColor.b, 1.0);
	else
		fragColor = texture(uTexture, v_TexCoord);
}