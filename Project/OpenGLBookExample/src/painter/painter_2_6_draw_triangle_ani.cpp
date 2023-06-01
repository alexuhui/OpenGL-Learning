#include "painter_2_6_draw_triangle_ani.h"

void Painter_2_6::init()
{
    title = "Example 2.6";

    vert = "./shader/s_2_6_draw_triangle_ani_vert.glsl";
    frag = "./shader/s_2_2_draw_point_frag.glsl";
}

void Painter_2_6::initWin(GLFWwindow* window)
{
    renderingProgram = Utils::createShaderProgram(vert, frag);
    initVaoVbo();
}

void Painter_2_6::display(GLFWwindow* window, double currentTime)
{
    glClear(GL_DEPTH_BUFFER_BIT);
    glClearColor(0.5, 0.5, 0.5, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(renderingProgram);

    x += inc;
    if (x > 1.0f) inc = -0.01f;
    else if (x < -1.0f) inc = 0.01f;
    GLuint offsetLoc = glGetUniformLocation(renderingProgram, "offset");
    glProgramUniform1f(renderingProgram, offsetLoc, x);

    glDrawArrays(GL_TRIANGLES, 0, 3);
}
