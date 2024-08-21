#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include<string>

#include"vao.h"
#include"ebo.h"
#include"camera.h"
#include"texture.h"


class Mesh
{
public:

	Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures);

	void Draw(Shader& shader, Camera& camera);

private:

	std::vector <Vertex> vertices;
	std::vector <GLuint> indices;
	std::vector <Texture> textures;

	VAO vao;
};
#endif