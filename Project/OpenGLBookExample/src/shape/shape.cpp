#include <cmath>
#include <vector>
#include <iostream>
#include <glm\glm.hpp>

#include "shape.h"

int Shape::getNumVertices() { return numVertices; }
int Shape::getNumIndices() { return numIndices; }
std::vector<int> Shape::getIndices() { return indices; }
std::vector<glm::vec3> Shape::getVertices() { return vertices; }
std::vector<glm::vec2> Shape::getTexCoords() { return texCoords; }
std::vector<glm::vec3> Shape::getNormals() { return normals; }
std::vector<glm::vec3> Shape::getTangents() { return tangents; }