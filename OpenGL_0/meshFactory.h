#ifndef  MESHFACTORY_CLASS_H
#define MESHFACTORY_CLASS_H

#include"mesh.h"


class MeshFactory
{
public:

	static Mesh CreateDefaultSquare();
	static Mesh CreateDefaultCube();
	static Mesh CreateDefaultModel();
};
#endif 