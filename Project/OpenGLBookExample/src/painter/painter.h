#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

class Painter
{
public:
	Painter();
	~Painter();
	
	virtual const char*  getTitle();
	virtual void init(GLFWwindow* window);
	virtual void display(GLFWwindow* window, double currentTime);

protected:
	virtual GLuint createShaderProgram(const char* vert, const char* frag);

	const char* readShaderSource(const char* filePath);

	void printShaderLog(GLuint shader);
	void printProgramLog(int prog);
	bool checkOpenGLError();

};