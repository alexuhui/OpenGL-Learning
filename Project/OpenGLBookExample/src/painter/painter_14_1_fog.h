#pragma once

#include "painter.h"

#include "..\shape\torus.h"

class Painter_14_1 : public Painter
{
public:
	void init();
	void initWin(GLFWwindow* window);
	void display(GLFWwindow* window, double currentTime);

protected:
	GLint texture{}, heightMap{};
	const char* tex0 = "";
	const char* tex_height = "";
    const char* model0 = "";
	ImportedModel myModel{};

private:
	float rotAmt = 0.0f;
};