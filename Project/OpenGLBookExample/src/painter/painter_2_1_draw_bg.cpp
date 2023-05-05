
#include "painter_2_1_draw_bg.h"


const char* Painter_2_1::getTitle()
{
	return "Example 2.1";
}

void Painter_2_1::display(GLFWwindow* window, double currentTime)
{
	glClearColor(0.5, 0.5, 0.5, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}