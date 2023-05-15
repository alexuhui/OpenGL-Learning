#include "painter_4_3_draw_cube_pyramid.h"

void Painter_4_3::init()
{
    title = "Example 4.3";

    vert = "./shader/s_4_1_draw_cube_vert.glsl";
    frag = "./shader/s_4_1_draw_cube_frag.glsl";

    cameraX = 0.0f, cameraY = 0.0f, cameraZ = 8.0f;
}

void Painter_4_3::initWin(GLFWwindow* window)
{
    this->Painter::initWin(window);

    renderingProgram = Utils::createShaderProgram(vert, frag);

    setupVertices(vertexPositions, pyramidPositions, sizeof(vertexPositions), sizeof(pyramidPositions));
}

void Painter_4_3::display(GLFWwindow* window, double currentTime)
{
    glClear(GL_DEPTH_BUFFER_BIT);
    glClearColor(0.5, 0.5, 0.5, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(renderingProgram);

    // 获取MV矩阵和投影矩阵的统一变量
    mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix");
    projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");

    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));

    // 构建视图矩阵、模型矩阵和视图-模型矩阵
    vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));
    
    glEnable(GL_CULL_FACE);

    // 绘制立方体 （使用0号缓冲区）
    mMat = glm::translate(glm::mat4(1.0f), glm::vec3(cubeLocX, cubeLocY, cubeLocZ));
    mvMat = vMat * mMat;
    glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
    // 将VBO关联给顶点着色器中相应的顶点属性
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    // 调整OpenGL设置，绘制模型
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glFrontFace(GL_CW);
    glDrawArrays(GL_TRIANGLES, 0, 36);


    // 绘制金字塔 （使用1号缓冲区）
    mMat = glm::translate(glm::mat4(1.0f), glm::vec3(pyrLocX, pyrLocY, pyrLocZ));
    mvMat = vMat * mMat;
    glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
    // 将VBO关联给顶点着色器中相应的顶点属性
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    // 调整OpenGL设置，绘制模型
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glFrontFace(GL_CCW);
    glDrawArrays(GL_TRIANGLES, 0, 18);
}

int Painter_4_3::getWidth()
{
    return 600;
}

int Painter_4_3::getHeight()
{
    return 600;
}
