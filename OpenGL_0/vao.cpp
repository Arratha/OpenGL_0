#include"vao.h"


VAO::VAO()
{
	glGenVertexArrays(1, &id);
}

void VAO::LinkAttributes(VBO& vbo, GLuint layout, GLuint componentsCount, GLenum type, GLsizeiptr stride, void* offset)
{
	vbo.Bind();
	
	glVertexAttribPointer(layout, componentsCount, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);

	vbo.Unbind();
}

void VAO::Bind()
{
	glBindVertexArray(id);
}

void VAO::Unbind()
{
	glBindVertexArray(0);
}

void VAO::Delete()
{
	glDeleteVertexArrays(1, &id);
}