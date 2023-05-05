#pragma once

#include "painter.h"

class Painter_2_5: public Painter
{
public:
	const char* getTitle();
	void init(GLFWwindow* window);
	void display(GLFWwindow* window, double currentTime);

private:

};