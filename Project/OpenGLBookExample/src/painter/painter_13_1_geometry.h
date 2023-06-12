#pragma once

#include "painter.h"
#include "../shape/torus.h"

class Painter_13_1 : public Painter
{
public:
	void init();
	void initWin(GLFWwindow* window);
	void display(GLFWwindow* window, double currentTime);

protected:
	const char* geom;

	GLint texture{};
	const char* tex0 = "";
	Torus myTorus = Torus(0.5f, 0.2f, 48);
};