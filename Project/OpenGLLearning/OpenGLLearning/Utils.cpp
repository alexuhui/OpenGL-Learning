#include <string>
#include <iostream>
#include <fstream>

#include "Utils.h"

using namespace std;

bool Utils::checkOpenGLError() {
    bool foundError = false;
    int glErr = glGetError();
    while (glErr != GL_NO_ERROR) {
        cout << "glError: " << glErr << endl;
        foundError = true;
        glErr = glGetError();
    }
    return foundError;
}

void Utils::printShaderLog(GLuint shader) {
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

void Utils::printProgramLog(int prog) {
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

string Utils::readShaderSource(const char* filePath)
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

GLuint Utils::createShaderProgram(const char* vp, const char* fp)
{
    int vertComplied;
    int fragComplied;
    int linked;

    string vertShaderStr = readShaderSource(vp);
    const char* vshaderSource = vertShaderStr.c_str();

    string fragShaderStr = readShaderSource(fp);
    const char* fshaderSource = fragShaderStr.c_str();

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

GLuint createShaderProgram(const char* vp, const char* gp, const char* fp)
{
    return 0;
}

GLuint createShaderProgram(const char* vp, const char* tCS, const char* tES, const char* fp)
{
    return 0;
}

GLuint createShaderProgram(const char* vp, const char* tCS, const char* tES, const char* gp, const char* fp)
{
    return 0;
}