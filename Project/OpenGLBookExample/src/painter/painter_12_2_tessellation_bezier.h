#pragma once

#include "painter.h"

class Painter_12_2 : public Painter
{
public:
	void init();
	void initWin(GLFWwindow* window);
	void display(GLFWwindow* window, double currentTime);

protected:
	GLint mvpLoc = 0;
	glm::mat4x4 mvpMat{};
	GLint texture{};
	const char* tex0 = "";

	const char* tessC = "";
	const char* tessE = "";
private:

};