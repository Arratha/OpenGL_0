#ifndef  MESHFACTORY_CLASS_H
#define MESHFACTORY_CLASS_H

#include"mesh.h"


class MeshFactory
{
public:

	static Mesh CreateDefaultSquare();
	static Mesh CreateDefaultCube();
	static Mesh CreateDefaultModel();

private:
	static void ReadCorner(std::string description,
		std::vector<glm::vec3>& v, std::vector<glm::vec2>& vt,
		std::vector<glm::vec3>& vn, std::vector<Vertex>& vertices);
	static std::vector<std::string> Split(std::string line, std::string delimiter);
};
#endif 