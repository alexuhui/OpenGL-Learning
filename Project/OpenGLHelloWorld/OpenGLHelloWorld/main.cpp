#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <fstream>
#include <string>

#define numVAOS 1

#define numVAOS 1

using namespace std;

<<<<<<< HEAD

GLuint renderingProgram;
GLuint vao[numVAOS];

GLuint createShaderProgram()
{
    const char *vshaderSource =
        "#version 430 \n"
        "void main(void) \n"
        "{ gl_Position = vec4(0.0, 0.0, 0.0, 1.0); }";

    const char* fshaderSource =
        "#version 430 \n"
        "out vec4 color; \n"
        "void main(void) \n"
        "{ color = vec4(0.0, 0.0, 1.0, 1.0); }";

    GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vShader, 1, &vshaderSource, NULL);
    glShaderSource(fShader, 1, &fshaderSource, NULL);

    glCompileShader(vShader);
    glCompileShader(fShader);

    GLuint vfProgram = glCreateProgram();
    glAttachShader(vfProgram, vShader);
    glAttachShader(vfProgram, fShader);
    glLinkProgram(vfProgram);

    return vfProgram;
}

void init(GLFWwindow* window) { 
    renderingProgram = createShaderProgram();
    glGenVertexArrays(numVAOS, vao);
    glBindVertexArray(vao[0]);
}
=======
>>>>>>> 79cadf9873deafba22356ca5ec54574d8d97f0ac

GLuint renderingProgram;
GLuint vao[numVAOS];


void printShaderLog(GLuint shader) {
    int len = 0;
    int chWrittn = 0;
    char* log;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
    if (len > 0) {
        log = (char*)malloc(len);
        glGetShaderInfoLog(shader, len, &chWrittn, log);
        cout << "Shader Info Log: " << log << endl;
        free(log);
    }
}

void printProgramLog(int prog) {
    int len = 0;
    int chWrittn = 0;
    char* log;
    glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);
    if (len > 0) {
        log = (char*)malloc(len);
        glGetProgramInfoLog(prog, len, &chWrittn, log);
        cout << "Program Info Log: " << log << endl;
        free(log);
    }
}

bool checkOpenGLError() {
    bool foundError = false;
    int glErr = glGetError();
    while (glErr != GL_NO_ERROR) {
        cout << "glError: " << glErr << endl;
        foundError = true;
        glErr = glGetError();
    }
    return foundError;
}

string readShaderSource(const char *filePath)
{
    string content;
    ifstream fileStream(filePath, ios::in);
    string line = "";
    while (!fileStream.eof())
    {
        getline(fileStream, line);
        content.append(line + "\n");
    }
    fileStream.close();
    return content;
}

GLuint createShaderProgram()
{
    int vertComplied;
    int fragComplied;
    int linked;

    string vertShaderStr = readShaderSource(".\\GLSL\\vertShader.glsl");
    const char* vshaderSource = vertShaderStr.c_str();
        /*"#version 430 \n"
        "void main(void) \n"
        "{ gl_Position = vec4(0.0, 0.0, 0.0, 1.0); }";*/


    string fragShaderStr = readShaderSource(".\\GLSL\\fragShader.glsl");
    const char* fshaderSource = fragShaderStr.c_str();
        /*"#version 430 \n"
        "out vec4 color; \n"
        "void main(void) \n"
        "{ if(gl_FragCoord.x < 640) color = vec4(1.0, 1.0, 0.0, 1.0); else color = vec4(0.0, 0.0, 1.0, 1.0); }";*/

    GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vShader, 1, &vshaderSource, NULL);
    glShaderSource(fShader, 1, &fshaderSource, NULL);

    glCompileShader(vShader);
    checkOpenGLError();
    glGetShaderiv(vShader, GL_COMPILE_STATUS, &vertComplied);
    if (vertComplied != 1)
    {
        cout << "vertex complition failed" << endl;
        printShaderLog(vShader);
    }

    glCompileShader(fShader);
    checkOpenGLError();
    glGetShaderiv(fShader, GL_COMPILE_STATUS, &fragComplied);
    if (vertComplied != 1)
    {
        cout << "fragment complition failed" << endl;
        printShaderLog(fShader);
    }


    GLuint vfProgram = glCreateProgram();
    glAttachShader(vfProgram, vShader);
    glAttachShader(vfProgram, fShader);
    glLinkProgram(vfProgram);
    checkOpenGLError();
    glGetProgramiv(vfProgram, GL_LINK_STATUS, &linked);
    if (linked != 1)
    {
        cout << "linking failed" << endl;
        printProgramLog(vfProgram);
    }

    return vfProgram;
}

void init(GLFWwindow* window) { 
    renderingProgram = createShaderProgram();
    glGenVertexArrays(numVAOS, vao);
    glBindVertexArray(vao[0]);
}

float x = 0.0f;
float inc = 0.01f;
float dirInc = 0.01f;
void display(GLFWwindow* window, double currentTime) {
<<<<<<< HEAD
    //glClearColor(0.5, 0.5, 0.5, 1.0);
    //glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(renderingProgram);
    glDrawArrays(GL_POINTS, 0, 1);
=======
    glClear(GL_DEPTH_BITS);
    glClearColor(0.5, 0.5, 0.5, 1.0);
    glClear(GL_COLOR_BUFFER_BIT); //清除背景

    glUseProgram(renderingProgram);
    
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //线框模型
    // glPointSize(120.0f);
    //glDrawArrays(GL_POINTS, 0, 1); //按点绘制

    x += dirInc;
    if (x > 0.7) dirInc = -inc;
    if (x < -0.7) dirInc = inc;
    GLint offsetLoc = glGetUniformLocation(renderingProgram, "offset");
    glProgramUniform1f(renderingProgram, offsetLoc, x);
    glDrawArrays(GL_TRIANGLES, 0, 3); //三角形绘制
>>>>>>> 79cadf9873deafba22356ca5ec54574d8d97f0ac
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