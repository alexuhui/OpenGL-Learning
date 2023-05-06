#include "painter_2_2_draw_point.h"

void Painter_2_2::init()
{
    title = "Example 2.2";

    vert = "./shader/s_2_2_draw_point_vert.glsl";
    frag = "./shader/s_2_2_draw_point_frag.glsl";
}

void Painter_2_2::initWin(GLFWwindow* window)
{
    renderingProgram = Utils::createShaderProgram(vert, frag);
    glGenVertexArrays(numVAOs, vao);
    glBindVertexArray(vao[0]);
}

void Painter_2_2::display(GLFWwindow* window, double currentTime)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(renderingProgram);

    if (size < 20) inc = 1.0f;
    else if (size > 80) inc = -1.0f;

    size += inc;
    glPointSize(size);
    glDrawArrays(GL_POINTS, 0, 1);
}
