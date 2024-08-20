#ifndef vertexArrayObject_CLASS_H
#define vertexArrayObject_CLASS_H

#include<glad/glad.h>
#include"vertexBufferObject.h"

class VertexArrayObject
{
public:

	GLuint id;

	VertexArrayObject();

	void LinkAttributes(VertexBufferObject& vbo, GLuint layout, GLuint componentsCount, GLenum type, GLsizeiptr stride, void* offset);
	void Bind();
	void Unbind();
	void Delete();
};
#endif