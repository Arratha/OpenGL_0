#ifndef vertexArrayObject_CLASS_H
#define vertexArrayObject_CLASS_H

#include<glad/glad.h>
#include"vbo.h"

class VAO
{
public:

	GLuint id;

	VAO();

	void LinkAttributes(VBO& vbo, GLuint layout, GLuint componentsCount, GLenum type, GLsizeiptr stride, void* offset);
	void Bind();
	void Unbind();
	void Delete();
};
#endif