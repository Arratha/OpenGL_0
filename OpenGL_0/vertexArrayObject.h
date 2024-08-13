#ifndef vertexArrayObject_CLASS_H
#define vertexArrayObject_CLASS_H

#include<glad/glad.h>
#include"vertexBufferObject.h"

class VertexArrayObject
{
public:

	GLuint id;

	VertexArrayObject();

	void LinkVertexBufferObject(VertexBufferObject& vbo, GLuint layout);
	void Bind();
	void Unbind();
	void Delete();
};
#endif