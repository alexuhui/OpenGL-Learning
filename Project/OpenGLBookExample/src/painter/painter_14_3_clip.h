#pragma once

#include "painter.h"

#include "..\shape\torus.h"

class Painter_14_3 : public Painter
{
public:
	void init();
	void initWin(GLFWwindow* window);
	void display(GLFWwindow* window, double currentTime);

protected:
	Torus myTorus = Torus(1.5f, 0.5f, 48);

	GLint aLoc{}, fLoc{}, flipLoc{};

private:
	float rotAmt = 0.0f;
};