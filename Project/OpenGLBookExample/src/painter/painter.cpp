#include "painter.h"

using namespace std;

Painter::Painter()
{
    cout << "Painter constructor" << endl;
}

Painter::~Painter()
{
    cout << "Painter destructor" << endl;
}

const char* Painter::getTitle()
{
    return title;
}

void Painter::init()
{
    cout << "Painter init" << endl;
}

void Painter::initWin(GLFWwindow* window)
{
    // 构建透视矩阵
    glfwGetFramebufferSize(window, &width, &height);
    aspect = (float)width / (float)height;
    pMat = glm::perspective(fov, aspect, nearClipPlane, farClipPlane); 
}

void Painter::display(GLFWwindow* window, double currentTime)
{
    cout << "Painter display" << endl;
}

int Painter::getWidth()
{
    return 890;
}

int Painter::getHeight()
{
    return 540;
}

void Painter::setupVertices(float* vertex, int size)
{
    glGenVertexArrays(1, vao);
    glBindVertexArray(vao[0]);
    glGenBuffers(numVBOs, vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, size, vertex, GL_STATIC_DRAW);
}

void Painter::setupVertices(float* vertex1, float* vertex2, int size1, int size2)
{
    glGenVertexArrays(1, vao);
    glBindVertexArray(vao[0]);
    glGenBuffers(numVBOs, vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, size1, vertex1, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, size2, vertex2, GL_STATIC_DRAW);
}

void Painter::setupVertices(Shape myShape)
{
    std::vector<int> ind = myShape.getIndices();
    std::vector<glm::vec3> vert = myShape.getVertices();
    std::vector<glm::vec2> tex = myShape.getTexCoords();
    std::vector<glm::vec3> norm = myShape.getNormals();

    std::vector<float> pvalues;
    std::vector<float> tvalues;
    std::vector<float> nvalues;

    int numIndices = myShape.getNumIndices();
    for (int i = 0; i < numIndices; i++) {
        pvalues.push_back((vert[ind[i]]).x);
        pvalues.push_back((vert[ind[i]]).y);
        pvalues.push_back((vert[ind[i]]).z);
        tvalues.push_back((tex[ind[i]]).s);
        tvalues.push_back((tex[ind[i]]).t);
        nvalues.push_back((norm[ind[i]]).x);
        nvalues.push_back((norm[ind[i]]).y);
        nvalues.push_back((norm[ind[i]]).z);
    }

    glGenVertexArrays(1, vao);
    glBindVertexArray(vao[0]);
    glGenBuffers(numVBOs, vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, pvalues.size() * 4, &pvalues[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, tvalues.size() * 4, &tvalues[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
    glBufferData(GL_ARRAY_BUFFER, nvalues.size() * 4, &nvalues[0], GL_STATIC_DRAW);
}

void Painter::windowReshapeCallback(GLFWwindow* window, int width, int height)
{
    aspect = (float)width / (float)height;
    glViewport(0, 0, width, height);
    pMat = glm::perspective(fov, aspect, nearClipPlane, farClipPlane);
}
