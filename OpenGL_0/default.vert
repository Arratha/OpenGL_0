#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec2 aTex;

out vec3 normal;
out vec3 color;
out vec2 texCoord;

uniform mat4 camMatrix;
uniform mat4 model;


void main()
{
	normal = aNormal;
	color = aColor;
	texCoord = aTex;
	
	vec3 position = vec3(model * vec4(aPos, 1.0f));
	gl_Position = camMatrix * vec4(position, 1.0);
}