#include "painter_6_3_draw_model.h"

void Painter_6_3::init()
{
    title = "Example 6.3";

    vert = "./shader/s_5_1_draw_pyramid_texture_vert.glsl";
    frag = "./shader/s_5_1_draw_pyramid_texture_frag.glsl";
    tex0 = "./res/model/shuttle/spstob_1.jpg";
    model0 = "./res/model/shuttle/shuttle.obj";
}

void Painter_6_3::initWin(GLFWwindow* window)
{
    this->Painter::initWin(window);

    cameraX = 0.0f, cameraY = 0.0f, cameraZ = 3.0f;

    renderingProgram = Utils::createShaderProgram(vert, frag);

    texture = Utils::loadTexture(tex0);

    initVaoVbo(3);
    myModel = ImportedModel(model0);
    setupVertices(myModel, 0);
}

void Painter_6_3::display(GLFWwindow* window, double currentTime)
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
    mvStack.push(vMat);

    mvStack.push(mvStack.top());

    if (posY > 1.2f)
        posStep = -0.01f;
    else if (posY < -1.2f)
        posStep = 0.01f;
    posY += posStep;

    mvStack.top() *= glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, posY, 0.0f));
    mvStack.push(mvStack.top());
    mvStack.top() *= rotate(glm::mat4(1.0f), (float)currentTime, glm::vec3(0.0, 1.0, 0.0));
    glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvStack.top()));
    mvStack.pop(); mvStack.pop(); mvStack.pop();

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, 0, 0);
    glEnableVertexAttribArray(1);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glFrontFace(GL_CCW);
    glDrawArrays(GL_TRIANGLES, 0, myModel.getNumVertices());
}
