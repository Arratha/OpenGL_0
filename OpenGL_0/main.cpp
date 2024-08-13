#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"shaderClass.h"
#include"vertexArrayObject.h"
#include"vertexBufferObject.h"
#include"elementsBufferObject.h"


GLFWwindow* CreateWindow();
void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);

//window settings
const unsigned int kBaseWidth = 800;
const unsigned int kBaseHeight = 600;

const float kBaseColor[4] = { 0.07f, 0.13f, 0.17f, 1.0f };




int main()
{
	glfwInit();

	GLFWwindow* window = CreateWindow();

	if (window == NULL)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	gladLoadGL();

	glViewport(0, 0, kBaseWidth, kBaseHeight);


	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,
		-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,
		0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,
		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f
	};

	GLuint indices[] =
	{
		0, 3, 5,
		3, 2, 4,
		5, 4, 1
	};


	Shader shaderProgram("default.vert", "default.frag");

	VertexArrayObject vertexArray;
	vertexArray.Bind();

	VertexBufferObject vertexBuffer(vertices, sizeof(vertices));
	ElementsBufferObject elementsBuffer(indices, sizeof(indices));

	vertexArray.LinkVertexBufferObject(vertexBuffer, 0);
	
	vertexArray.Unbind();
	vertexBuffer.Unbind();
	elementsBuffer.Unbind();


	glClearColor(kBaseColor[0], kBaseColor[1], kBaseColor[2], kBaseColor[3]);

	glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback);
	

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(kBaseColor[0], kBaseColor[1], kBaseColor[2], kBaseColor[3]);
		glClear(GL_COLOR_BUFFER_BIT);
		
		shaderProgram.Activate();

		vertexArray.Bind();

		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}

GLFWwindow* CreateWindow()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* result = glfwCreateWindow(kBaseWidth, kBaseHeight, "OpenGL_0", NULL, NULL);

	return result;
}

void FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}