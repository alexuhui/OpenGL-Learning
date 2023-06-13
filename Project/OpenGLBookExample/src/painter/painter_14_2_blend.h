#pragma once

#include "painter.h"

#include "..\shape\torus.h"

class Painter_14_2 : public Painter
{
public:
	void init();
	void initWin(GLFWwindow* window);
	void display(GLFWwindow* window, double currentTime);

protected:
    const char* model0 = "";
	ImportedModel myModel{};
	Torus myTorus = Torus(0.8f, 0.6f, 48);

	GLint aLoc{}, fLoc{};

private:
	float rotAmt = 0.0f;
};