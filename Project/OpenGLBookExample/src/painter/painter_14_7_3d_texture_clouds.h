#pragma once

#include "painter.h"

#include "..\shape\torus.h"
#include "../shape/sphere_half.h"
#include "../shape/sphere.h"

class Painter_14_7 : public Painter
{
public:
	void init();
	void initWin(GLFWwindow* window);
	void display(GLFWwindow* window, double currentTime);

protected:
	GLint aLoc{}, fLoc{}, flipLoc{}, tLoc{}, dOffsetLoc{};
	glm::mat4 texRot{};
	float depth = 0.01f; // depth for 3rd dimension of 3D noise texture

private:
	const char* noiseTexPath = "";
	float rotAmt = 0.0f;
	const int noiseHeight = 200;
	const int noiseWidth = 200;
	const int noiseDepth = 200;
	double*** noise;

	HalfSphere halfSphere = HalfSphere(48);
	GLuint skyTexture{};

	void fillDataArray(GLubyte data[]);
	GLuint buildNoiseTexture();
	void generateNoise();
	double smoothNoise(double x1, double y1, double z1);
	double turbulence(double x, double y, double z, double size);

	inline double logistic(double x) {
		double k = 0.2; // tunable haziness of clouds
		return (1.0 / (1.0 + pow(2.718, -k * x)));
	}
};