#include "painter_2_5_draw_triangle.h"

#define numVAOs 1

GLuint static renderingProgram;
GLuint static vao[numVAOs];

static const char* vert = "./shader/s_2_5_draw_triangle_vert.glsl";
static const char* frag = "./shader/s_2_2_draw_point_frag.glsl";

const char* Painter_2_5::getTitle()
{
    return "Example 2.5";
}

void Painter_2_5::init(GLFWwindow* window)
{
    renderingProgram = createShaderProgram(vert, frag);
    glGenVertexArrays(numVAOs, vao);
    glBindVertexArray(vao[0]);
}

void Painter_2_5::display(GLFWwindow* window, double currentTime)
{
    glUseProgram(renderingProgram);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
