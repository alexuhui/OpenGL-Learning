#pragma once

#include "painter.h"

class Painter_12_6: public Painter
{
public:
	void init();
	void initWin(GLFWwindow* window);
	void display(GLFWwindow* window, double currentTime);

protected:
	GLint mvpLoc = 0;
	glm::mat4x4 mvpMat{};

	const char* tessC = "";
	const char* tessE = "";

	const char* tex0 = "";
	const char* tex_height = "";
	const char* tex_normal = "";

	GLint texture = 0, heightMap = 0;

private:
	float transDir = 0.05f;
};