#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Utils.h"

using namespace std;

#define numVAOS 1
#define numVBOS 2

float cameraX, cameraY, cameraZ;
float cubeLocX, cubeLocY, cubeLocZ;
float pyramidLocX, pyramidLocY, pyramidLocZ;

GLuint renderingProgram;
GLuint vao[numVAOS];
GLuint vbo[numVBOS];

GLuint mLoc, vLoc, mvLoc, projLoc, tfLoc;
int width, height;
float aspect;
glm::mat4 pMat, vMat, mMat, mvMat;
//glm::mat4 tMat, rMat;
float timeFactor;

void setupVertices(void) {    // 36个顶点，12个三角形，组成了放置在原点处的2×2×2立方体
    float cubeVertPositions[108] = {
       -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f,
       1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f,
       1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f,
       1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f,
       1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
       -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
       -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
       -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
       -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f,
       1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,
       -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f,
       1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, -1.0f
    };

    float pyramidVertPositions[54] = {
       -1.0f, -1.0f, 1.0f,      1.0f, -1.0f, 1.0f,      0.0f, 1.0f, 0.0f,
       1.0f, -1.0f, 1.0f,       1.0f, -1.0f, -1.0f,     0.0f, 1.0f, 0.0f,
       1.0f, -1.0f, -1.0f,      -1.0f, -1.0f, -1.0f,    0.0f, 1.0f, 0.0f,
       -1.0f, -1.0f, -1.0f,     -1.0f, -1.0f, 1.0f,     0.0f, 1.0f, 0.0f,
       -1.0f, -1.0f, -1.0f,     1.0f, -1.0f, 1.0f,      -1.0f, -1.0f, 1.0f,
       1.0f, -1.0f, 1.0f,       -1.0f, -1.0f, -1.0f,    1.0f, -1.0f, -1.0f,
    };

    glGenVertexArrays(1, vao);
    glBindVertexArray(vao[0]);
    glGenBuffers(numVBOS, vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertPositions), cubeVertPositions, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(pyramidVertPositions), pyramidVertPositions, GL_STATIC_DRAW);
}


void init(GLFWwindow* window) {
    renderingProgram = Utils::createShaderProgram(".\\GLSL\\vertShader.glsl", ".\\GLSL\\fragShader.glsl");

    cameraX = 0.0f; cameraY = 0.0f; cameraZ = 300.0f;
    cubeLocX = 0.0f; cubeLocY = -2.0f; cubeLocZ = 0.0f;
    pyramidLocX = 0.0f; pyramidLocY = -2.0f; pyramidLocZ = 0.0f;

    setupVertices();
}

void transformCube(GLint mvLoc, GLint projLoc, float tf)
{
    glm::mat4 tMat, rMat;
    tMat = glm::translate(glm::mat4(1.0),
        glm::vec3(sin(0.35f * tf) * 2.0f, sin(0.52f * tf) * 2.0f, sin(0.7f * tf) * 2.0f));
    rMat = glm::rotate(glm::mat4(1.0),
        1.75f * (float)tf, glm::vec3(0.0f, 1.0f, 0.0f));
    rMat = glm::rotate(rMat,
        1.75f * (float)tf, glm::vec3(1.0f, 0.0f, 0.0f));
    rMat = glm::rotate(rMat,
        1.75f * (float)tf, glm::vec3(0.0f, 0.0f, 1.0f));

    mMat = tMat * rMat;
    mvMat = vMat * mMat;

    glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glDrawArrays(GL_TRIANGLES, 0, 36000); //draw triangles
}


void transformCubeInstanced(GLint mLoc, GLint vLoc, GLint projLoc, float currentTime)
{
    glUniformMatrix4fv(mLoc, 1, GL_FALSE, glm::value_ptr(mMat));
    glUniformMatrix4fv(vLoc, 1, GL_FALSE, glm::value_ptr(vMat));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));

    tfLoc = glGetUniformLocation(renderingProgram, "tf");
    timeFactor = currentTime;
    glUniform1f(tfLoc, timeFactor);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glDrawArraysInstanced(GL_TRIANGLES, 0, 36, 10000);
}

void transformPyramidInstanced(GLint mLoc, GLint vLoc, GLint projLoc, float currentTime)
{
    glUniformMatrix4fv(mLoc, 1, GL_FALSE, glm::value_ptr(mMat));
    glUniformMatrix4fv(vLoc, 1, GL_FALSE, glm::value_ptr(vMat));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));

    tfLoc = glGetUniformLocation(renderingProgram, "tf");
    timeFactor = currentTime;
    glUniform1f(tfLoc, timeFactor);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glDrawArraysInstanced(GL_TRIANGLES, 0, 18, 10000);
}

void display(GLFWwindow* window, double currentTime) {
    glClear(GL_DEPTH_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(renderingProgram);

    //mLoc = glGetUniformLocation(renderingProgram, "m_matrix");
    vLoc = glGetUniformLocation(renderingProgram, "v_matrix");
    //mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix");
    projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");

    glfwGetFramebufferSize(window, &width, &height);
    aspect = (float)width / (float)height;
    pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f); // 1.0472 radians = 60 degrees
    vMat = glm::translate(glm::mat4(1.0f), glm::vec3(- cameraX, - cameraY, - cameraZ));

    mMat = glm::translate(glm::mat4(1.0f), glm::vec3(cubeLocX, cubeLocY, cubeLocZ));
    transformCubeInstanced(mLoc,vLoc, projLoc, (float)currentTime);

    mMat = glm::translate(glm::mat4(1.0f), glm::vec3(pyramidLocX, pyramidLocY, pyramidLocZ));
    transformPyramidInstanced(mLoc, vLoc, projLoc, (float)currentTime+0.5);
}

int main(void) {
    if (!glfwInit()) { exit(EXIT_FAILURE); }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    GLFWwindow* window = glfwCreateWindow(1280, 760, "Chapter4 - program 1", NULL, NULL);
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