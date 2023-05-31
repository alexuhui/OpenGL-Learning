#pragma once

#include "painter.h"

#include "..\shape\torus.h"

class Painter_6_2 : public Painter
{
public:
	void init();
	void initWin(GLFWwindow* window);
	void display(GLFWwindow* window, double currentTime);

    int getWidth();
    int getHeight();

protected:
    GLint texture{};
    const char* tex0 = "";
    Torus myTorus = Torus(0.5f, 0.2f, 48);
};