#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../utils/utils.h"

#define numVAOs 1
#define numVBOs 2

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
};