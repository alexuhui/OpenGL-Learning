#include <iostream>

#include "painter_include.h"

using namespace std;

Painter* painter;
void draw();
void windowReshapeCallback(GLFWwindow* win, int newWidth, int newHeight);

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
        else if (chapter == 5)
        {
            if (section == 1) { painter = new Painter_5_1(); draw(); continue; }
        }
        else if (chapter == 6)
        {
            if (section == 1) { painter = new Painter_6_1(); draw(); continue; }
            if (section == 2) { painter = new Painter_6_2(); draw(); continue; }
            if (section == 3) { painter = new Painter_6_3(); draw(); continue; }
        }
        else if (chapter == 7)
        {
            if (section == 1) { painter = new Painter_7_1(); draw(); continue; }
            if (section == 2) { painter = new Painter_7_2(); draw(); continue; }
            if (section == 3) { painter = new Painter_7_3(); draw(); continue; }
        }
        else if(chapter == 8)
        {
            if (section == 1) { painter = new Painter_8_1(); draw(); continue; }
            if (section == 2) { painter = new Painter_8_2(); draw(); continue; }
        }
        else if (chapter == 9)
        {
            if (section == 1) { painter = new Painter_9_1(); draw(); continue; }
            if (section == 2) { painter = new Painter_9_2(); draw(); continue; }
            if (section == 3) { painter = new Painter_9_3(); draw(); continue; }
        }
        else if (chapter == 10)
        {
            if (section == 1) { painter = new Painter_10_1(); draw(); continue; }
            if (section == 2) { painter = new Painter_10_2(); draw(); continue; }
            if (section == 4) { painter = new Painter_10_4(); draw(); continue; }
            if (section == 5) { painter = new Painter_10_5(); draw(); continue; }
        }
        else if(chapter == 12)
        {
            if (section == 1) { painter = new Painter_12_1(); draw(); continue; }
            if (section == 2) { painter = new Painter_12_2(); draw(); continue; }
            if (section == 3) { painter = new Painter_12_3(); draw(); continue; }
            if (section == 4) { painter = new Painter_12_4(); draw(); continue; }
            if (section == 5) { painter = new Painter_12_5(); draw(); continue; }
            if (section == 6) { painter = new Painter_12_6(); draw(); continue; }
        }
        else if(chapter == 13)
        {
            if (section == 1) { painter = new Painter_13_1(); draw(); continue; }
            if (section == 2) { painter = new Painter_13_2(); draw(); continue; }
            if (section == 3) { painter = new Painter_13_3(); draw(); continue; }
            if (section == 4) { painter = new Painter_13_4(); draw(); continue; }
            if (section == 5) { painter = new Painter_13_5(); draw(); continue; }
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

    painter->init();
    GLFWwindow* window = glfwCreateWindow(painter->getWidth(), painter->getHeight(), painter->getTitle(), NULL, NULL);
    glfwSetWindowSizeCallback(window, windowReshapeCallback);

    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) { exit(EXIT_FAILURE); }
    glfwSwapInterval(1);

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

void windowReshapeCallback(GLFWwindow* win, int newWidth, int newHeight)
{
    painter->windowReshapeCallback(win, newWidth, newHeight);
}