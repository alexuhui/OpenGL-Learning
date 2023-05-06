#pragma once

#include "painter.h"

class Painter_2_1 : public Painter
{
public:
	void init();
	void display(GLFWwindow* window, double currentTime);
};