#pragma once

#include "painter_model.h"

#include "..\shape\torus.h"

class Painter_6_3 : public Painter_Model
{
public:
	void init();
	void initWin(GLFWwindow* window);
	void display(GLFWwindow* window, double currentTime);

protected:
	GLint texture{};
	const char* tex0 = "";
    const char* model0 = "";
	ImportedModel myModel;

private:
	float posY = 0.0f;
	float posStep = 0.01f;
};