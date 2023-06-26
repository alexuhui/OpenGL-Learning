#pragma once

#include "painter.h"

#include "..\shape\torus.h"

class Painter_14_6 : public Painter
{
public:
	void init();
	void initWin(GLFWwindow* window);
	void display(GLFWwindow* window, double currentTime);

protected:
	GLint aLoc{}, fLoc{}, flipLoc{}, tLoc{};
	const char* model0 = "";
	ImportedModel dolphinObj{};
	glm::mat4 texRot{};

private:
	const char* noiseTexPath = "";
	float rotAmt = 0.0f;
	GLuint noiseTexture{};
	const int noiseHeight = 300;
	const int noiseWidth = 300;
	const int noiseDepth = 300;
	double*** noise;

	void fillDataArray(GLubyte data[]);
	GLuint buildNoiseTexture();
	void generateNoise();
	double smoothNoise(double x1, double y1, double z1);
	double turbulence(double x, double y, double z, double size);
};