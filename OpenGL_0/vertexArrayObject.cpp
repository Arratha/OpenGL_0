#include"vertexArrayObject.h"

VertexArrayObject::VertexArrayObject()
{
	glGenVertexArrays(1, &id);
}

void VertexArrayObject::LinkVertexBufferObject(VertexBufferObject& vbo, GLuint layout)
{
	vbo.Bind();
	
	glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);	
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