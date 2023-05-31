#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stack>

#include "../utils/utils.h"
#include "../shape/shape.h"

#define numVAOs 1
#define numVBOs 4

using namespace std;

class Painter
{
public:
	Painter();
	~Painter();
	
	virtual const char*  getTitle();
	virtual void init();
	virtual void initWin(GLFWwindow* window);
	virtual void display(GLFWwindow* window, double currentTime);
	virtual void windowReshapeCallback(GLFWwindow* window, int width, int height);

	virtual int getWidth();
	virtual int getHeight();

protected:
	const char* title = "Example";
	const char* vert = "";
	const char* frag = "";
	GLuint renderingProgram = 0;
	GLuint vao[numVAOs]{};
	GLuint vbo[numVBOs]{};

	virtual void setupVertices(float* vertex, int size);
	virtual void setupVertices(float* vertex1, float* vertex2, int size1, int size2);
	virtual void setupVertices(Shape myShape);
	virtual void setupVertices(Shape myShape, bool useIndexBuf);

	int width = 0, height = 0;
	float aspect = 1.0f;
	float nearClipPlane = 0.1f, farClipPlane = 1000.0f;
	float fov = 1.0472f; // 1.0472 radians = 60 degrees

	float cameraX = 0.0f, cameraY = 0.0f, cameraZ = 12.0f;

	GLuint mLoc{}, vLoc{}, mvLoc{}, projLoc{};
	glm::mat4 tMat{}, rMat{}, sMat{};
	glm::mat4 mMat{}, vMat{}, pMat{}, mvMat{};

	stack<glm::mat4> mvStack;

private:
	
	
};