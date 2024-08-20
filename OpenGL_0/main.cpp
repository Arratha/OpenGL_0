#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>


#include"shaderClass.h"
#include"vertexArrayObject.h"
#include"vertexBufferObject.h"
#include"elementsBufferObject.h"
#include"texture.h";

GLFWwindow* CreateWindow();
void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);

//window settings
const unsigned int kBaseWidth = 800;
const unsigned int kBaseHeight = 800;

GLfloat kBaseColor[4] = { 0.07f, 0.13f, 0.17f, 1.0f };


int main()
{
	//Initialization
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

	glClearColor(kBaseColor[0], kBaseColor[1], kBaseColor[2], kBaseColor[3]);

	glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback);


	//Vertices coordinates and indices
	GLfloat vertices[] =
	{//     COORDINATES     /        COLORS      /   TexCoord  //
		-0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,	0.0f, 0.0f,
		-0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,	0.0f, 1.0f,
		 0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,	1.0f, 1.0f,
		 0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,	1.0f, 0.0f
	};

	GLuint indices[] =
	{
		0,2,1,
		0,3,2
	};


	//Create shader program for default shaders
	Shader shaderProgram("default.vert", "default.frag");

	VertexArrayObject vertexArray;
	vertexArray.Bind();

	VertexBufferObject vertexBuffer(vertices, sizeof(vertices));
	ElementsBufferObject elementsBuffer(indices, sizeof(indices));

	//Link coordinates
	vertexArray.LinkAttributes(vertexBuffer, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	//Link colors
	vertexArray.LinkAttributes(vertexBuffer, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	//Ling texture coordinates
	vertexArray.LinkAttributes(vertexBuffer, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	
	//Unbind is unnecessary in this case 
	vertexArray.Unbind();
	vertexBuffer.Unbind();
	elementsBuffer.Unbind();
	

	//Texture
	Texture texture("TestTexture.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	texture.texUnit(shaderProgram, "tex0", 0);

	//Main loop
	while (!glfwWindowShouldClose(window))
	{
		//Clear
		glClearColor(kBaseColor[0], kBaseColor[1], kBaseColor[2], kBaseColor[3]);
		glClear(GL_COLOR_BUFFER_BIT);
		
		//Draw
		shaderProgram.Activate();
		texture.Bind();
		vertexArray.Bind();

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		
		//Swap buffer and poll events (who would have guess?)
		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	//Clean up
	glfwDestroyWindow(window);
	glfwTerminate();

	vertexArray.Delete();
	vertexBuffer.Delete();
	elementsBuffer.Delete();
	texture.Delete();

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

//Window resize handler
void FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}