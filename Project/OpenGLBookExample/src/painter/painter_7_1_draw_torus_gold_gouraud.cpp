#include "painter_7_1_draw_torus_gold_gouraud.h"

void Painter_7_1::init()
{
    title = "Example 7.1";

    vert = "./shader/s_7_1_gouraud_vert.glsl";
    frag = "./shader/s_7_1_gouraud_frag.glsl";
}

void Painter_7_1::initWin(GLFWwindow* window)
{
    this->Painter::initWin(window);

    cameraX = 0.0f, cameraY = 0.0f, cameraZ = 2.0f;

    renderingProgram = Utils::createShaderProgram(vert, frag);

    initVaoVbo(4);
    texture = Utils::loadTexture(tex0);
    setupVertices(myTorus, 0, true);
}

void Painter_7_1::display(GLFWwindow* window, double currentTime)
{
    glClear(GL_DEPTH_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(renderingProgram);

    mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix");
    projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");
    nLoc = glGetUniformLocation(renderingProgram, "norm_matrix");

    vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));

    mMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -1.0f));
    mMat *= glm::rotate(mMat, Utils::toRadians(35.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    currentLightPos = glm::vec3(lightLoc.x, lightLoc.y, lightLoc.z);
    amt += 0.5f;
    rMat = glm::rotate(glm::mat4(1.0f), Utils::toRadians(amt), glm::vec3(0.0f, 0.0f, 1.0f));
    currentLightPos = glm::vec3(rMat * glm::vec4(currentLightPos, 1.0f));

    installLights(renderingProgram, vMat, matAmb, matDif, matSpe, matShi);

    mvMat = vMat * mMat;
    invTrMat = glm::transpose(glm::inverse(mvMat));

    glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));
    glUniformMatrix4fv(nLoc, 1, GL_FALSE, glm::value_ptr(invTrMat));

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[3]);
    glDrawElements(GL_TRIANGLES, myTorus.getNumIndices(), GL_UNSIGNED_INT, 0);
}

int Painter_7_1::getWidth()
{
    return 600;
}

int Painter_7_1::getHeight()
{
    return 600;
}
