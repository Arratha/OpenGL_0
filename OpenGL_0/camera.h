#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include"shaderClass.h"

class Camera
{
public:

	Camera(int width, int height, glm::vec3 position);

	void UpdateMatrix(float FOVdeg, float nearPlane, float farPlane);
	void UpdateSize(int width, int height);
	void Matrix(Shader& shader, const char* uniform);
	void Inputs(GLFWwindow* window);

private:

	glm::vec3 position;
	glm::mat4 cameraMatrix = glm::mat4(1.0f);
	glm::vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

	bool firstClick = true;

	int width;
	int height;

	float speed = 1.0f;
	float sensitivity = 100.0f;

	void Move(GLFWwindow* window);
	void Rotate(GLFWwindow* window);
};
#endif