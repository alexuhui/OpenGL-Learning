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

void Painter::initVaoVbo(int vboCnt, int vaoCnt)
{
    numVaos = vaoCnt;
    numVbos = vboCnt;

    vao = new GLuint[numVaos];
    vbo = new GLuint[numVbos];

    glGenVertexArrays(numVaos, vao);
    glBindVertexArray(vao[0]);
    glGenBuffers(numVbos, vbo);
}

void  Painter::setupVbo(float* bufData, int size, int index)
{
    glBindBuffer(GL_ARRAY_BUFFER, vbo[index]);
    glBufferData(GL_ARRAY_BUFFER, size, bufData, GL_STATIC_DRAW);
}

void  Painter::setupVbo(int* bufData, int size, int index)
{
    glBindBuffer(GL_ARRAY_BUFFER, vbo[index]);
    glBufferData(GL_ARRAY_BUFFER, size, bufData, GL_STATIC_DRAW);
}

/// <summary>
/// 直接把顶点属性对应到每个顶点索引上
/// </summary>
/// <param name="myShape"></param>
void Painter::setupVertices(Shape myShape, int startIndex)
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

    setupVbo(&pvalues[0], pvalues.size() * 4, startIndex);
    setupVbo(&tvalues[0], tvalues.size() * 4, startIndex + 1);
    setupVbo(&nvalues[0], nvalues.size() * 4, startIndex + 2);
}

/// <summary>
/// useIndexBuf = true
/// 顶点属性和顶点对应，把顶点索引单独推到渲染管线
/// </summary>
/// <param name="myShape"></param>
/// <param name="useIndexBuf"></param>
void Painter::setupVertices(Shape myShape, int startIndex, bool useIndexBuf)
{
    if (!useIndexBuf)
    {
        setupVertices(myShape, startIndex);
        return;
    }

    std::vector<int> ind = myShape.getIndices();
    std::vector<glm::vec3> vert = myShape.getVertices();
    std::vector<glm::vec2> tex = myShape.getTexCoords();
    std::vector<glm::vec3> norm = myShape.getNormals();

    std::vector<float> pvalues;
    std::vector<float> tvalues;
    std::vector<float> nvalues;

    for (int i = 0; i < myShape.getNumVertices(); i++) {
        pvalues.push_back(vert[i].x);
        pvalues.push_back(vert[i].y);
        pvalues.push_back(vert[i].z);
        tvalues.push_back(tex[i].s);
        tvalues.push_back(tex[i].t);
        nvalues.push_back(norm[i].x);
        nvalues.push_back(norm[i].y);
        nvalues.push_back(norm[i].z);
    }
    
    setupVbo(&pvalues[0], pvalues.size() * 4, startIndex);
    setupVbo(&tvalues[0], tvalues.size() * 4, startIndex + 1);
    setupVbo(&nvalues[0], nvalues.size() * 4, startIndex + 2);
    setupVbo(&ind[0], ind.size() * 4, startIndex + 3);
}

void Painter::setupVertices(ImportedModel myModel, int startIndex)
{
    std::vector<glm::vec3> vert = myModel.getVertices();
    std::vector<glm::vec2> tex = myModel.getTextureCoords();
    std::vector<glm::vec3> norm = myModel.getNormals();
    int numObjVertices = myModel.getNumVertices();

    std::vector<float> pvalues;       // 顶点位置
    std::vector<float> tvalues;       // 纹理坐标
    std::vector<float> nvalues;       // 法向量

    if (numObjVertices == 0)
        return;

    for (int i = 0; i < numObjVertices; i++) {
        pvalues.push_back((vert[i]).x);
        pvalues.push_back((vert[i]).y);
        pvalues.push_back((vert[i]).z);
        tvalues.push_back((tex[i]).s);
        tvalues.push_back((tex[i]).t);
        nvalues.push_back((norm[i]).x);
        nvalues.push_back((norm[i]).y);
        nvalues.push_back((norm[i]).z);
    }

    setupVbo(&pvalues[0], pvalues.size() * 4, startIndex);
    setupVbo(&tvalues[0], tvalues.size() * 4, startIndex + 1);
    setupVbo(&nvalues[0], nvalues.size() * 4, startIndex + 2);
}

void Painter::installLights(int renderingProgram, glm::mat4 vMatrix, float * matAmb, float * matDif, float* matSpe, float matShi) {
    transformed = glm::vec3(vMatrix * glm::vec4(currentLightPos, 1.0));
    lightPos[0] = transformed.x;
    lightPos[1] = transformed.y;
    lightPos[2] = transformed.z;

    // get the locations of the light and material fields in the shader
    globalAmbLoc = glGetUniformLocation(renderingProgram, "globalAmbient");
    ambLoc = glGetUniformLocation(renderingProgram, "light.ambient");
    diffLoc = glGetUniformLocation(renderingProgram, "light.diffuse");
    specLoc = glGetUniformLocation(renderingProgram, "light.specular");
    posLoc = glGetUniformLocation(renderingProgram, "light.position");
    mambLoc = glGetUniformLocation(renderingProgram, "material.ambient");
    mdiffLoc = glGetUniformLocation(renderingProgram, "material.diffuse");
    mspecLoc = glGetUniformLocation(renderingProgram, "material.specular");
    mshiLoc = glGetUniformLocation(renderingProgram, "material.shininess");

    //  set the uniform light and material values in the shader
    glProgramUniform4fv(renderingProgram, globalAmbLoc, 1, globalAmbient);
    glProgramUniform4fv(renderingProgram, ambLoc, 1, lightAmbient);
    glProgramUniform4fv(renderingProgram, diffLoc, 1, lightDiffuse);
    glProgramUniform4fv(renderingProgram, specLoc, 1, lightSpecular);
    glProgramUniform3fv(renderingProgram, posLoc, 1, lightPos);
    glProgramUniform4fv(renderingProgram, mambLoc, 1, matAmb);
    glProgramUniform4fv(renderingProgram, mdiffLoc, 1, matDif);
    glProgramUniform4fv(renderingProgram, mspecLoc, 1, matSpe);
    glProgramUniform1f(renderingProgram, mshiLoc, matShi);
}

void Painter::setupShadowBuffers(GLFWwindow* window) {
    glfwGetFramebufferSize(window, &width, &height);
    scSizeX = width;
    scSizeY = height;

    glGenFramebuffers(1, &shadowBuffer);

    glGenTextures(1, &shadowTex);
    glBindTexture(GL_TEXTURE_2D, shadowTex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32,
        scSizeX, scSizeY, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);

    // may reduce shadow border artifacts
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

void Painter::windowReshapeCallback(GLFWwindow* window, int width, int height)
{
    aspect = (float)width / (float)height;
    glViewport(0, 0, width, height);
    pMat = glm::perspective(fov, aspect, nearClipPlane, farClipPlane);
}
