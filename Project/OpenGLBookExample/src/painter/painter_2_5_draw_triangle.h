#pragma once

#include "painter.h"

#define numVAOs 1

class Painter_2_5: public Painter
{
public:
	void init();
	void initWin(GLFWwindow* window);
	void display(GLFWwindow* window, double currentTime);

private:
};