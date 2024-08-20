#include"vertexArrayObject.h"

VertexArrayObject::VertexArrayObject()
{
	glGenVertexArrays(1, &id);
}

void VertexArrayObject::LinkAttributes(VertexBufferObject& vbo, GLuint layout, GLuint componentsCount, GLenum type, GLsizeiptr stride, void* offset)
{
	vbo.Bind();
	
	glVertexAttribPointer(layout, componentsCount, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);

	vbo.Unbind();
}

void VertexArrayObject::Bind()
{
	glBindVertexArray(id);
}

void VertexArrayObject::Unbind()
{
	glBindVertexArray(0);
}

void VertexArrayObject::Delete()
{
	glDeleteVertexArrays(1, &id);
}