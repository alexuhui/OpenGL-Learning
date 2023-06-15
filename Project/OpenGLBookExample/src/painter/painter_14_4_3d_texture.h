#pragma once

#include "painter.h"

#include "..\shape\torus.h"

class Painter_14_4 : public Painter
{
public:
	void init();
	void initWin(GLFWwindow* window);
	void display(GLFWwindow* window, double currentTime);

protected:
	Torus myTorus = Torus(1.5f, 0.5f, 48);

	GLint aLoc{}, fLoc{}, flipLoc{};
	const char* model0 = "";
	ImportedModel dolphinObj{};

private:
	float rotAmt = 0.0f;
	GLuint stripesTexture;
	const int texHeight = 300;
	const int texWidth = 300;
	const int texDepth = 300;
	double*** tex3Dpattern;
	const char* tex3dPath = "";

	void fillDataArray(GLubyte data[]);
	int build3DTexture();
	void generate3Dpattern();

};