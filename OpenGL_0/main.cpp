#include "windows.h"

#include"meshFactory.h"

GLFWwindow* CreateGLWindow();
void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);


//window settings
const unsigned int kBaseWidth = 800;
const unsigned int kBaseHeight = 800;

const float kFPS = 60.0f;

GLfloat kBaseColor[4] = { 0.07f, 0.13f, 0.17f, 1.0f };


Camera camera(kBaseWidth, kBaseHeight, glm::vec3(0.0f, 0.0f, 2.0f));


int main()
{
	//Initialization
	glfwInit();

	GLFWwindow* window = CreateGLWindow();

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


	Mesh cube = MeshFactory::CreateDefaultModel();

	Shader shaderProgram("default.vert", "default.frag");

	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.id, "model"), 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));

	camera = Camera(kBaseWidth, kBaseHeight, glm::vec3(0.0f, 0.0f, 2.0f));


	glEnable(GL_DEPTH_TEST);

	
	//Main loop
	while (!glfwWindowShouldClose(window))
	{
		//Clear
		glClearColor(kBaseColor[0], kBaseColor[1], kBaseColor[2], kBaseColor[3]);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.Inputs(window);

		camera.UpdateMatrix(45.0f, 0.1f, 1000.0f);
		cube.Draw(shaderProgram, camera);

		//Swap buffer and poll events (who would have guess?)
		glfwSwapBuffers(window);
		glfwPollEvents();	

		Sleep(1000 / kFPS);
	}


	//Clean up
	glfwDestroyWindow(window);
	glfwTerminate();

	shaderProgram.Delete();
	
	return 0;
}

GLFWwindow* CreateGLWindow()
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

	camera.UpdateSize(width, height);
}