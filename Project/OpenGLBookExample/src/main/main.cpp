#include <iostream>

#include "painter_include.h"

using namespace std;

Painter* painter;
void draw();

int main(void) {
    

    int chapter;
    int section;
    while (true)
    {
        cout << "input chapter and section (0 to exit) : " << endl;
        cin >> chapter;
        if (chapter == 0)break;
        cin >> section;
        if (section == 0)break;

        if (chapter == 2)
        {
            if (section == 1) { painter = new Painter_2_1(); draw(); continue;}
            else if (section == 2 || section == 3 || section == 4) { painter = new Painter_2_2(); draw(); continue; }
            else if (section == 5) { painter = new Painter_2_5(); draw(); continue; }
            else if (section == 6 ){painter = new Painter_2_6(); draw();continue;}
        }
        else if(chapter == 4)
        {
            if (section == 1) { painter = new Painter_4_1(); draw(); continue; }
            if (section == 2) { painter = new Painter_4_2(); draw(); continue; }
            if (section == 3) { painter = new Painter_4_3(); draw(); continue; }
            if (section == 4) { painter = new Painter_4_4(); draw(); continue; }
        }

        cout << "Example " << chapter << "."  << section << " not exist..." << endl;
        cout << endl;
    }
}

void draw()
{
    if (!glfwInit()) { exit(EXIT_FAILURE); }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    GLFWwindow* window = glfwCreateWindow(painter->getWidth(), painter->getHeight(), painter->getTitle(), NULL, NULL);

    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) { exit(EXIT_FAILURE); }
    glfwSwapInterval(1);

    painter->init();
    painter->initWin(window);

    while (!glfwWindowShouldClose(window)) {
        painter->display(window, glfwGetTime());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    //exit(EXIT_SUCCESS);
    cout << painter->getTitle() << " closed ..." << endl;
    cout << endl;
}