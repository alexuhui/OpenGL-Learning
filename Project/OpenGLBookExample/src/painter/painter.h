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
	GLuint renderingProgram1 = 0;
	GLuint renderingProgram2 = 0;

	GLuint* vao{};
	GLuint* vbo{};

	int numVaos = 1;
	int numVbos = 1;
	virtual void initVaoVbo(int vboCnt = 1, int vaoCnt = 1);
	virtual void setupVbo(float* bufData, int size, int index);
	virtual void setupVbo(int* bufData, int size, int index);

	virtual int setupVertices(Shape myShape, int startIndex);
	virtual int setupVertices(Shape myShape, int startIndex, bool useIndexBuf);
	virtual int setupVertices(ImportedModel myModel, int startIndex);

	virtual void installLights(int renderingProgram, glm::mat4 vMatrix, float* matAmb, float* matDif, float* matSpe, float matShi);
	virtual void setupShadowBuffers(GLFWwindow* window);


	int width = 0, height = 0;
	float aspect = 1.0f;
	float nearClipPlane = 0.1f, farClipPlane = 1000.0f;
	float fov = 1.0472f; // 1.0472 radians = 60 degrees

	float cameraX = 0.0f, cameraY = 0.0f, cameraZ = 12.0f;

	glm::vec3 lightLoc = glm::vec3(5.0f, 2.0f, 2.0f);
	float amt = 0.0f;
	GLuint nLoc = 0;
	GLuint globalAmbLoc = 0, ambLoc = 0, diffLoc = 0, specLoc = 0, posLoc = 0, mambLoc = 0, mdiffLoc = 0, mspecLoc = 0, mshiLoc = 0;

	GLuint mLoc = 0, vLoc = 0, mvLoc = 0, projLoc = 0, sLoc = 0;
	glm::mat4 tMat{}, rMat{}, sMat{};
	glm::mat4 mMat{}, vMat{}, pMat{}, mvMat{};
	glm::mat4 invTrMat{};
	glm::vec3 currentLightPos{}, transformed{};
	float lightPos[3]{};

	stack<glm::mat4> mvStack{};

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

	// bronze material
	float* bMatAmb = Utils::bronzeAmbient();
	float* bMatDif = Utils::bronzeDiffuse();
	float* bMatSpe = Utils::bronzeSpecular();
	float bMatShi = Utils::bronzeShininess();

	// silver material
	float* sMatAmb = Utils::silverAmbient();
	float* sMatDif = Utils::silverDiffuse();
	float* sMatSpe = Utils::silverSpecular();
	float sMatShi = Utils::silverShininess();

	// shadow stuff
	int scSizeX = 0, scSizeY = 0;
	GLuint shadowTex{}, shadowBuffer{};
	glm::mat4 lightVmatrix{};
	glm::mat4 lightPmatrix{};
	glm::mat4 shadowMVP1{};
	glm::mat4 shadowMVP2{};
	glm::mat4 bMat = glm::mat4(
		0.5f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f);; //biases matrix
	
	glm::vec3 origin = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

private:
	
	
};