#ifndef  VertexBufferObject_CLASS_H
#define VertexBufferObject_CLASS_H

#include<glad/glad.h>

class  VertexBufferObject
{
public:

	GLuint id;

	VertexBufferObject(GLfloat* vertices, GLsizeiptr size);

	void Bind();
	void Unbind();
	void Delete();
};
#endif 