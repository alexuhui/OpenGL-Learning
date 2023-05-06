#pragma once

#include "painter.h"

#define numVAOs 1

class Painter_2_6: public Painter
{
public:
	void init();
	void initWin(GLFWwindow* window);
	void display(GLFWwindow* window, double currentTime);

private:
	float x = 0.0f;
	float inc = 0.01f;
};