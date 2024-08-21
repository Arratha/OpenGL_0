#include"meshFactory.h"


Mesh MeshFactory::CreateDefaultSquare()
{
	std::vector<Vertex> vertices =
	{
		Vertex{glm::vec3(-0.5f, -0.5f,  0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
		Vertex{glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
		Vertex{glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
		Vertex{glm::vec3(0.5f, -0.5f,  0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)}
	};

	std::vector<GLuint> indices =
	{
		0,2,1,
		0,3,2
	};

	std::vector<Texture> textures = {
		Texture{"TestTexture.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE}
	};

	return Mesh(vertices, indices, textures);
}

Mesh MeshFactory::CreateDefaultCube()
{
	std::vector<Vertex> vertices =
	{
		Vertex{glm::vec3(-0.1f, -0.1f,  0.1f),  glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
		Vertex{glm::vec3(-0.1f, -0.1f, -0.1f),  glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f)},
		Vertex{glm::vec3(0.1f, -0.1f, -0.1f),  glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
		Vertex{glm::vec3(0.1f, -0.1f,  0.1f),  glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f)},

		Vertex{glm::vec3(-0.1f,  0.1f,  0.1f),  glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)},
		Vertex{glm::vec3(-0.1f,  0.1f, -0.1f),  glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f)},
		Vertex{glm::vec3(0.1f,  0.1f, -0.1f),  glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
		Vertex{glm::vec3(0.1f,  0.1f,  0.1f),  glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)}
	};

	std::vector<GLuint> indices =
	{
		0, 1, 2,
		0, 2, 3,
		0, 4, 7,
		0, 7, 3,
		3, 7, 6,
		3, 6, 2,
		2, 6, 5,
		2, 5, 1,
		1, 5, 4,
		1, 4, 0,
		4, 5, 6,
		4, 6, 7
	};

	std::vector<Texture> textures = {
		Texture{"TestTexture.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE}
	};

	return Mesh(vertices, indices, textures);
}

Mesh MeshFactory::CreateDefaultModel()
{
	const char* fileName = "TestModel.obj";

	std::vector<glm::vec3> v;
	std::vector<glm::vec2> vt;
	std::vector<glm::vec3> vn;
	std::vector<Vertex> vertices;

	//It is faster to read the file twice, getting the number of objects and reserving memory for them once
	size_t vertexCount = 0;
	size_t texcoordCount = 0;
	size_t normalCount = 0;
	size_t facesCount = 0;

	std::string line;
	std::vector<std::string> splittedLine;

	std::ifstream file;

	file.open(fileName);
	while (std::getline(file, line))
	{
		splittedLine = Split(line, " ");

		if (!splittedLine[0].compare("v"))
		{
			vertexCount++;
		}

		else if (!splittedLine[0].compare("vt")) 
		{
			texcoordCount++;
		}

		else if (!splittedLine[0].compare("vn")) 
		{
			normalCount++;
		}

		//In obj face can be represented as polygon
		//Number of triangles equals angles of polygon - 2 and first element of splitted line is key
		else if (!splittedLine[0].compare("f"))
		{
			facesCount += splittedLine.size() - 3;
		}
	}
	file.close();


	v.reserve(vertexCount);
	vt.reserve(texcoordCount);
	vn.reserve(normalCount);
	vertices.reserve(facesCount);

	int lineIndex = 0;

	file.open(fileName);
	while (std::getline(file, line))
	{
		std::cout << lineIndex << " " << line << std::endl;
		lineIndex++;

		splittedLine = Split(line, " ");

		if (!splittedLine[0].compare("v"))
		{
			v.push_back(glm::vec3(std::stof(splittedLine[1]), std::stof(splittedLine[2]), std::stof(splittedLine[3])));
		}

		else if (!splittedLine[0].compare("vt"))
		{
			vt.push_back(glm::vec2(std::stof(splittedLine[1]), std::stof(splittedLine[2])));
		}

		else if (!splittedLine[0].compare("vn"))
		{
			vn.push_back(glm::vec3(std::stof(splittedLine[1]), std::stof(splittedLine[2]), std::stof(splittedLine[3])));
		}

		else if (!splittedLine[0].compare("f"))
		{
			size_t triangleCount = splittedLine.size() - 3;

			for (size_t i = 0; i < triangleCount; ++i)
			{
				ReadCorner(splittedLine[1], v, vt, vn, vertices);
				ReadCorner(splittedLine[2 + i], v, vt, vn, vertices);
				ReadCorner(splittedLine[3 + i], v, vt, vn, vertices);
			}
		}
	}
	file.close();

	//I don't understand how I can get indices for obj
	//Things should be better with them
	std::vector<GLuint> indices;

	std::vector<Texture> textures = {
		Texture{"Placeholder.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE}
	};

	return Mesh(vertices, indices, textures);
}

void MeshFactory::ReadCorner(std::string description,
	std::vector<glm::vec3>& v, std::vector<glm::vec2>& vt,
	std::vector<glm::vec3>& vn, std::vector<Vertex>& vertices)
{
	std::vector<std::string> v_vt_vn = Split(description, "/");

	glm::vec3 pos = v[std::stol(v_vt_vn[0]) - 1];
	glm::vec3 normal = vn[std::stol(v_vt_vn[2]) - 1];
	glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec2 texCoord = vt[std::stol(v_vt_vn[1]) - 1];

	Vertex vertex{ pos, normal, color, texCoord };

	vertices.push_back(vertex);
}

std::vector<std::string> MeshFactory::Split(std::string line, std::string delimiter)
{
	std::vector<std::string> splitLine;

	size_t pos = 0;
	std::string token;
	while ((pos = line.find(delimiter)) != std::string::npos) {
		token = line.substr(0, pos);
		splitLine.push_back(token);
		line.erase(0, pos + delimiter.length());
	}
	splitLine.push_back(line);

	return splitLine;
}