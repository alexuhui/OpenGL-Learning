#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stack>

#include "../utils/utils.h"
#include "../shape/shape.h"
#include "../model/imported_model.h"

#define numVAOs 1
#define numVBOs 5

using namespace std;

class Painter
{
public:
	Painter();
	~Painter();
	
	virtual const char*  getTitle();
	virtual void init();
	virtual void initWin(GLFWwindow* window);
	virtual void display(GLFWwindow* window, double currentTime);
	virtual void windowReshapeCallback(GLFWwindow* window, int width, int height);

	virtual int getWidth();
	virtual int getHeight();

protected:
	const char* title = "Example";
	const char* vert = "";
	const char* frag = "";
	GLuint renderingProgram = 0;
	GLuint vao[numVAOs]{};
	GLuint vbo[numVBOs]{};

	virtual void setupVertices(float* vertex, int size);
	virtual void setupVertices(float* vertex1, float* vertex2, int size1, int size2);
	virtual void setupVertices(Shape myShape);
	virtual void setupVertices(Shape myShape, bool useIndexBuf);
	virtual void setupVertices(ImportedModel myModel);
	virtual void installLights(int renderingProgram, glm::mat4 vMatrix, float* matAmb, float* matDif, float* matSpe, float matShi);

	int width = 0, height = 0;
	float aspect = 1.0f;
	float nearClipPlane = 0.1f, farClipPlane = 1000.0f;
	float fov = 1.0472f; // 1.0472 radians = 60 degrees

	float cameraX = 0.0f, cameraY = 0.0f, cameraZ = 12.0f;

	glm::vec3 lightLoc = glm::vec3(5.0f, 2.0f, 2.0f);
	float amt = 0.0f;
	GLuint nLoc;
	GLuint globalAmbLoc, ambLoc, diffLoc, specLoc, posLoc, mambLoc, mdiffLoc, mspecLoc, mshiLoc;

	GLuint mLoc{}, vLoc{}, mvLoc{}, projLoc{};
	glm::mat4 tMat{}, rMat{}, sMat{};
	glm::mat4 mMat{}, vMat{}, pMat{}, mvMat{};
	glm::mat4 invTrMat;
	glm::vec3 currentLightPos, transformed;
	float lightPos[3];

	stack<glm::mat4> mvStack;

	// white light
	float globalAmbient[4] = { 0.7f, 0.7f, 0.7f, 1.0f };
	float lightAmbient[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	float lightDiffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float lightSpecular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

	// gold material
	float* matAmb = Utils::goldAmbient();
	float* matDif = Utils::goldDiffuse();
	float* matSpe = Utils::goldSpecular();
	float matShi = Utils::goldShininess();

private:
	
	
};