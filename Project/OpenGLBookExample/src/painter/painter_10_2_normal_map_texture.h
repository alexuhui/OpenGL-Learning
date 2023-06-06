#pragma once

#include "painter.h"

#include "..\shape\sphere.h"

class Painter_10_2 : public Painter
{
public:
	void init();
	void initWin(GLFWwindow* window);
	void display(GLFWwindow* window, double currentTime);

protected:
	GLint texture{}, texNormal{};
    const char* tex0 = "";
	const char* tex_nor = "";
    Sphere mySphere = Sphere(32);
};