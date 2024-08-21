#version 330 core

out vec4 FragColor;

//Нормали здесь для того, чтобы были. Я их что, зря читал что ли?
in vec3 normal;
in vec3 color;
in vec2 texCoord;

uniform sampler2D tex0;

void main()
{
	vec4 texture = texture(tex0, texCoord);

	FragColor = vec4(texture.x * color.x, texture.y * color.y, texture.z * color.z, texture.z);
}