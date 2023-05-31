#pragma once

#include <cmath>
#include <vector>
#include <glm\glm.hpp>

class Shape
{
public:
	int getNumVertices();
	int getNumIndices();
	std::vector<int> getIndices();
	std::vector<glm::vec3> getVertices();
	std::vector<glm::vec2> getTexCoords();
	std::vector<glm::vec3> getNormals();
	std::vector<glm::vec3> getTangents(); //切向量
	std::vector<glm::vec3> getStangents();//切向量，同getTangents
	std::vector<glm::vec3> getTtangents();//负切向量

protected:
	int numVertices;
	int numIndices;
	std::vector<int> indices;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> texCoords;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec3> sTangents;
	std::vector<glm::vec3> tTangents;

	float toRadians(float degrees);
};