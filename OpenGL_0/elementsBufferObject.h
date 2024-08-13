#ifndef ElementsBufferObject_CLASS_H
#define ElementsBufferObject_CLASS_H

#include<glad/glad.h>

class ElementsBufferObject
{
public:
	GLuint id;
	
	ElementsBufferObject(GLuint* indices, GLsizeiptr size);

	void Bind();
	void Unbind();
	void Delete();
};

#endif