#pragma once

#include "painter.h"

#include "..\shape\torus.h"

class Painter_8_1 : public Painter
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
    const char* model0 = "";
    const char* vert2 = "";
    const char* frag2 = "";
    Torus myTorus = Torus(0.6f, 0.4f, 48);
    ImportedModel myModel{};

    glm::vec3 torusLoc = glm::vec3(1.6f, 0.0f, -0.3f);
    glm::vec3 pyrLoc = glm::vec3(-1.0f, 0.1f, 0.3f);
    glm::vec3 lightLoc = glm::vec3(-3.8f, 2.2f, 1.1f);

    void passOne();
    void passTwo();
};