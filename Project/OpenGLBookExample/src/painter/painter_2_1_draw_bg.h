#pragma once

#include "painter.h"

class Painter_2_1 : public Painter
{
public:
	const char* getTitle();
	void display(GLFWwindow* window, double currentTime);
};