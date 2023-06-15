#pragma once

#include "painter.h"

#include "..\shape\torus.h"

class Painter_14_5 : public Painter
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
	GLuint noiseTexture;
	const int noiseHeight = 300;
	const int noiseWidth = 300;
	const int noiseDepth = 300;
	double*** noise;

	void fillDataArray(GLubyte data[]);
	GLuint buildNoiseTexture();
	void generateNoise();
	double smoothNoise(double x1, double y1, double z1);
	double turbulence(double x, double y, double z, double size);

	inline double logistic(double x) {
		double k = 3.0;
		return (1.0 / (1.0 + pow(2.718, -k * x)));
	}
};