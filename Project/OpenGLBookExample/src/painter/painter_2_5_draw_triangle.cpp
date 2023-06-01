#include "painter_2_5_draw_triangle.h"

void Painter_2_5::init()
{
    title = "Example 2.5";

    vert = "./shader/s_2_5_draw_triangle_vert.glsl";
    frag = "./shader/s_2_2_draw_point_frag.glsl";
}

void Painter_2_5::initWin(GLFWwindow* window)
{
    renderingProgram = Utils::createShaderProgram(vert, frag);
    initVaoVbo();
}

void Painter_2_5::display(GLFWwindow* window, double currentTime)
{
    glUseProgram(renderingProgram);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
