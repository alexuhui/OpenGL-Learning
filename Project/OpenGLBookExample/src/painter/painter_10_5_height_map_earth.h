#pragma once

#include "painter.h"

#include "..\shape\sphere.h"

class Painter_10_5 : public Painter
{
public:
	void init();
	void initWin(GLFWwindow* window);
	void display(GLFWwindow* window, double currentTime);

protected:
	GLint texture{}, heightMap{}, normalMap{};
	const char* tex0 = "";
	const char* tex_normal = "";
	const char* tex_height = "";
	
	Sphere mySphere = Sphere(96);

private:

};