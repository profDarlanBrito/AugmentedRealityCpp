#version 410 core

layout(location = 0) in vec3 position; // Input vertex position
layout(location = 1) in vec3 vertexColor; // Output fragment color
layout(location = 2) in vec2 TexCoord; // Input vertex normal
layout(location = 3) in vec3 Normal;

uniform mat4 uModelMatrix;
uniform mat4 uPerspectiveMatrix;
uniform mat4 uViewMatrix;	


// The vertex shader outputs the position of the vertex to the fragment shader.
out vec3 v_vertexColor;
out vec2 v_TexCoord;
out vec3 v_Normal;

void main() {
	// Set the vertex color to a solid red
	v_vertexColor = vertexColor;
	vec4 newPosition = uPerspectiveMatrix * uViewMatrix * uModelMatrix * vec4(position, 1.0);
	// Set the position of the vertex in clip space
	gl_Position = vec4(newPosition.x, newPosition.y,newPosition.z, newPosition.w);
	v_TexCoord = TexCoord; // Pass texture coordinates to fragment shader
	v_Normal = Normal; // Pass normal vector to fragment shader
}
// The vertex shader takes a 3D position as input and sets the gl_Position