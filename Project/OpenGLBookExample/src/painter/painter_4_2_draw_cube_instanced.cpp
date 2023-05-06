#include "painter_4_2_draw_cube_instanced.h"

void Painter_4_2::init()
{
    title = "Example 4.1";

    vert = "./shader/s_4_2_draw_cube_vert_instanced.glsl";
    frag = "./shader/s_4_1_draw_cube_frag.glsl";
}

void Painter_4_2::initWin(GLFWwindow* window)
{
    renderingProgram = Utils::createShaderProgram(vert, frag);

    setupVertices(vertexPositions, sizeof(vertexPositions));
}

void Painter_4_2::display(GLFWwindow* window, double currentTime)
{
    glClear(GL_DEPTH_BUFFER_BIT);
    glClearColor(0.5, 0.5, 0.5, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(renderingProgram);

    // 获取MV矩阵和投影矩阵的统一变量
    vLoc = glGetUniformLocation(renderingProgram, "v_matrix");
    projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");

    // 构建透视矩阵
    glfwGetFramebufferSize(window, &width, &height);
    aspect = (float)width / (float)height;
    pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f); // 1.0472 radians = 60 degrees

    // 构建视图矩阵、模型矩阵和视图-模型矩阵
    vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));
    
    // 构建（和变换）mMat的计算被移动到顶点着色器中去了
    // 在 C++ 应用程序中不再需要构建MV矩阵
    glUniformMatrix4fv(vLoc, 1, GL_FALSE, glm::value_ptr(vMat));   // 着色器需要视图矩阵的统一变量
    float timeFactor = ((float)currentTime);                             // 为了获得时间因子信息
    tfLoc = glGetUniformLocation(renderingProgram, "timeFactor");          // （着色器也需要它）
    glUniform1f(tfLoc, (float)timeFactor);

    // 将VBO关联给顶点着色器中相应的顶点属性
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    // 调整OpenGL设置，绘制模型
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glDrawArraysInstanced(GL_TRIANGLES, 0, 36, 24);
}

int Painter_4_2::getWidth()
{
    return 600;
}

int Painter_4_2::getHeight()
{
    return 600;
}
