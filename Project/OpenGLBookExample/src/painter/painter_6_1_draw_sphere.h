#pragma once

#include "painter.h"

#include "..\shape\sphere.h"

class Painter_6_1 : public Painter
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
    Sphere mySphere = Sphere(4);
};