#pragma once

#include "painter.h"

#include "..\shape\torus.h"

class Painter_7_1 : public Painter
{
public:
	void init();
	void initWin(GLFWwindow* window);
	void display(GLFWwindow* window, double currentTime);

    int getWidth();
    int getHeight();

protected:
    GLint texture{};
    const char* tex0 = "";
    Torus myTorus = Torus(0.5f, 0.2f, 48);

    glm::vec3 lightLoc = glm::vec3(5.0f, 2.0f, 2.0f);
    float amt = 0.0f;

    // variable allocation for display
    GLuint nLoc;
    GLuint globalAmbLoc, ambLoc, diffLoc, specLoc, posLoc, mambLoc, mdiffLoc, mspecLoc, mshiLoc;
    glm::mat4 invTrMat;
    glm::vec3 currentLightPos, transformed;
    float lightPos[3];

    // white light
    float globalAmbient[4] = { 0.7f, 0.7f, 0.7f, 1.0f };
    float lightAmbient[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
    float lightDiffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float lightSpecular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

    // gold material
    float* matAmb = Utils::silverAmbient();
    float* matDif = Utils::silverDiffuse();
    float* matSpe = Utils::silverSpecular();
    float matShi = Utils::silverShininess();

    void installLights(glm::mat4 vMatrix);
};