#include "painter_4_1_draw_cube.h"

void Painter_4_1::init()
{
    title = "Example 4.1";

    vert = "./shader/s_4_1_draw_cube_vert.glsl";
    frag = "./shader/s_4_1_draw_cube_frag.glsl";

    cameraX = 0.0f, cameraY = 0.0f, cameraZ = 40.0f;
    cubeLocX = 0.0f, cubeLocY = -2.0f, cubeLocZ = 0.0f;
}

void Painter_4_1::initWin(GLFWwindow* window)
{
    renderingProgram = Utils::createShaderProgram(vert, frag);

    initVaoVbo();
    setupVbo(vertexPositions, sizeof(vertexPositions), 0);
}

void Painter_4_1::display(GLFWwindow* window, double currentTime)
{
    glClear(GL_DEPTH_BUFFER_BIT);
    glClearColor(0.5, 0.5, 0.5, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(renderingProgram);

    // 获取MV矩阵和投影矩阵的统一变量
    mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix");
    projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");

    // 构建透视矩阵
    glfwGetFramebufferSize(window, &width, &height);
    aspect = (float)width / (float)height;
    pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f); // 1.0472 radians = 60 degrees

    // 构建视图矩阵、模型矩阵和视图-模型矩阵
    vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));
    
    //绘制单个cube
    //drawCube(currentTime, 2.0f);
    //绘制多个cube
    for (int i = 0; i < 72; i++)
    {
        drawCube(currentTime * 1.0f + i * 0.5f, 10.0f);
    }
}

void Painter_4_1::drawCube(double timeFactor, float tranFactor)
{
    //只计算了固定位移变换矩阵
    //mMat = glm::translate(glm::mat4(1.0f), glm::vec3(cubeLocX, cubeLocY, cubeLocZ));

    //平移变换  使用当前时间来计算x，y和z的不同变换
    tMat = glm::translate(glm::mat4(1.0f), 
        glm::vec3(sin(0.35f * timeFactor) * tranFactor,
            cos(0.52f * timeFactor) * tranFactor,
            sin(0.7f * timeFactor) * tranFactor * 2.0f));

    //旋转变换 用1.75来调整旋转速度
    float rot = 0.175f * (float)timeFactor;
    rMat = glm::rotate(glm::mat4(1.0f), rot, glm::vec3(0.0f, 1.0f, 0.0f));
    rMat = glm::rotate(rMat, rot, glm::vec3(1.0f, 0.0f, 0.0f));
    rMat = glm::rotate(rMat, rot, glm::vec3(0.0f, 0.0f, 1.0f));
    //缩放变换
    float scale = 1;// 0.75f + sin(timeFactor) * 0.25f;
    sMat = glm::scale(glm::mat4(1.0f), glm::vec3(scale, scale, scale));

    //模型矩阵(组合 平移 旋转 缩放变换)
    mMat = tMat * rMat * sMat;

    // 视图-模型矩阵
    mvMat = vMat * mMat;

    // 将透视矩阵和MV矩阵复制给相应的统一变量
    glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));

    // 将VBO关联给顶点着色器中相应的顶点属性
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    // 调整OpenGL设置，绘制模型
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

int Painter_4_1::getWidth()
{
    return 600;
}

int Painter_4_1::getHeight()
{
    return 600;
}
