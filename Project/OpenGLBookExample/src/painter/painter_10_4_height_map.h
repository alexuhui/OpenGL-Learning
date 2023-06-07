#pragma once

#include "painter.h"

#include "..\shape\torus.h"

class Painter_10_4 : public Painter
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
	float posY = 0.0f;
	float posStep = 0.01f;
};