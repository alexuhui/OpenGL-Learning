#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include "Utils.h"
#include "math.h"

#define numVAOS 1

using namespace std;

GLuint renderingProgram;
GLuint vao[numVAOS];

void init(GLFWwindow* window) {
    renderingProgram = Utils::createShaderProgram(".\\GLSL\\vertShader.glsl", ".\\GLSL\\fragShader.glsl");
    glGenVertexArrays(numVAOS, vao);
    glBindVertexArray(vao[0]);
}

float x = 0.0f;
float inc = 0.01f;
float dirInc = 0.01f;
float rotZ = 0.0f;
float rotInc = 0.1f;
void display(GLFWwindow* window, double currentTime) {
    glClear(GL_DEPTH_BITS);
    glClearColor(0.5, 0.5, 0.5, 1.0);
    glClear(GL_COLOR_BUFFER_BIT); 

    glUseProgram(renderingProgram);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //draw line
    // glPointSize(120.0f);
    //glDrawArrays(GL_POINTS, 0, 1); //draw point

    x += dirInc;
    if (x > 0.7) dirInc = -inc;
    if (x < -0.7) dirInc = inc;
    GLint offsetLoc = glGetUniformLocation(renderingProgram, "offset");
    glProgramUniform1f(renderingProgram, offsetLoc, x);

    rotZ = fmod(rotZ + rotInc, 3.14159f * 2.0f);
    GLint rotZLoc = glGetUniformLocation(renderingProgram, "rotZ");
    glProgramUniform1f(renderingProgram, rotZLoc, rotZ);

    glDrawArrays(GL_TRIANGLES, 0, 3); //draw triangles
}

int main(void) {
    if (!glfwInit()) { exit(EXIT_FAILURE); }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    GLFWwindow* window = glfwCreateWindow(1280, 760, "Chapter2 - program1", NULL, NULL);
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) { exit(EXIT_FAILURE); }
    glfwSwapInterval(1);

    init(window);

    while (!glfwWindowShouldClose(window)) {
        display(window, glfwGetTime());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}