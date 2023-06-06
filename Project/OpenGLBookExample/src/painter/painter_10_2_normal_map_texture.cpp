#include "painter_10_2_normal_map_texture.h"

void Painter_10_2::init()
{
    title = "Example 10.2";

    vert = "./shader/s_10_2_normal_map_texture_vert.glsl";
    frag = "./shader/s_10_2_normal_map_texture_frag.glsl";

    /*vert = "./shader/s_7_2_phong_vert.glsl";
    frag = "./shader/s_7_2_phong_flag.glsl";*/

    tex0 = "./res/img/moon.jpg";
    tex_nor = "./res/img/moonNORMAL.jpg";
}

void Painter_10_2::initWin(GLFWwindow* window)
{
    this->Painter::initWin(window);

    cameraX = 0.0f, cameraY = 0.0f, cameraZ = 3.0f;
    lightLoc = glm::vec3(-5.0f, 2.0f, 5.0f);

    renderingProgram = Utils::createShaderProgram(vert, frag);

    texture = Utils::loadTexture(tex0);
    texNormal = Utils::loadTexture(tex_nor);

    initVaoVbo(4);
    setupVertices(mySphere, 0);
}

void Painter_10_2::display(GLFWwindow* window, double currentTime)
{
    glClear(GL_DEPTH_BUFFER_BIT);
    glClearColor(0.5, 0.5, 0.5, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(renderingProgram);

    // 获取MV矩阵和投影矩阵的统一变量
    mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix");
    projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");
    nLoc = glGetUniformLocation(renderingProgram, "norm_matrix");

    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));

    // 构建视图矩阵、模型矩阵和视图-模型矩阵
    vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));
    mMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    mMat = glm::rotate(mMat, Utils::toRadians(20.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    mMat *= rotate(glm::mat4(1.0f), (float)currentTime * 0.1f, glm::vec3(0.0, 1.0, 0.0));

    currentLightPos = glm::vec3(lightLoc.x, lightLoc.y, lightLoc.z);
    installLights(renderingProgram, vMat, sMatAmb, sMatDif, sMatSpe, sMatShi);

    mvMat = vMat * mMat;
    glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
    invTrMat = glm::transpose(glm::inverse(mvMat));
    glUniformMatrix4fv(nLoc, 1, GL_FALSE, glm::value_ptr(invTrMat));

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, 0, 0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
    glVertexAttribPointer(2, 3, GL_FLOAT, false, 0, 0);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[3]);
    glVertexAttribPointer(3, 3, GL_FLOAT, false, 0, 0);
    glEnableVertexAttribArray(3);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texNormal);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glFrontFace(GL_CCW);
    glDrawArrays(GL_TRIANGLES, 0, mySphere.getNumIndices());
}
