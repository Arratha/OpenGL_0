#include"elementsBufferObject.h"

ElementsBufferObject::ElementsBufferObject(GLuint* indices, GLsizeiptr size)
{
	glGenBuffers(1, &id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

void ElementsBufferObject::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void ElementsBufferObject::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void ElementsBufferObject::Delete()
{
	glDeleteBuffers(1, &id);
}