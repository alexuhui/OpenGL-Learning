#include "painter_14_3_clip.h"

void Painter_14_3::init()
{
    title = "Example 14.3";

    vert = "./shader/s_14_3_clip_vert.glsl";
    frag = "./shader/s_14_3_clip_frag.glsl";
}

void Painter_14_3::initWin(GLFWwindow* window)
{
    this->Painter::initWin(window);

    cameraX = 0.0f; cameraY = 0.3f; cameraZ = 4.0f;

    renderingProgram = Utils::createShaderProgram(vert, frag);

	currentLightPos = glm::vec3(5.0f, 2.0f, 2.0f);

    initVaoVbo(4);
    setupVertices(myTorus, 0, true);
}

void Painter_14_3::display(GLFWwindow* window, double currentTime)
{
	glClear(GL_DEPTH_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(renderingProgram);

	mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix");
	projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");
	nLoc = glGetUniformLocation(renderingProgram, "norm_matrix");
	flipLoc = glGetUniformLocation(renderingProgram, "flipNormal");

	vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));

	mMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	mMat = glm::rotate(mMat, Utils::toRadians(35.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	currentLightPos = glm::vec3(lightLoc.x, lightLoc.y, lightLoc.z);

	installLights(renderingProgram,vMat, matAmb, matDif, matSpe, matShi);

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
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glEnable(GL_CLIP_DISTANCE0);

	glUniform1i(flipLoc, 1.0f);
	glFrontFace(GL_CCW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[3]);
	glDrawElements(GL_TRIANGLES, myTorus.getNumIndices(), GL_UNSIGNED_INT, 0);

	glUniform1i(flipLoc, -1.0f);
	glFrontFace(GL_CW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[3]);
	glDrawElements(GL_TRIANGLES, myTorus.getNumIndices(), GL_UNSIGNED_INT, 0);
}
