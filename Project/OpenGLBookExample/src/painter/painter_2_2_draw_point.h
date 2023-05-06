#pragma once

#include "painter.h"

class Painter_2_2 : public Painter
{
public:
	void init();
	void initWin(GLFWwindow* window);
	void display(GLFWwindow* window, double currentTime);

protected:

private:
	float size = 30.0f;
	float inc = 1.0f;
};