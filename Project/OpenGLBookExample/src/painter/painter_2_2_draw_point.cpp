#include "painter_2_2_draw_point.h"


#include <stdio.h>
#include <io.h>
//#include <string>

#define numVAOs 1

GLuint renderingProgram;
GLuint vao[numVAOs];

const char* vert = "./shader/s_2_2_draw_point_vert.glsl";
const char* frag = "./shader/s_2_2_draw_point_frag.glsl";

const char* Painter_2_2::getTitle()
{
    return "Example 2.2";
}

void Painter_2_2::init(GLFWwindow* window)
{
    renderingProgram = createShaderProgram(vert, frag);
    glGenVertexArrays(numVAOs, vao);
    glBindVertexArray(vao[0]);
}

void Painter_2_2::display(GLFWwindow* window, double currentTime)
{
    glUseProgram(renderingProgram);
    glPointSize(30.0f);
    glDrawArrays(GL_POINTS, 0, 1);
}
