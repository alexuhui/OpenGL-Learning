#include "painter_14_2_blend.h"

void Painter_14_2::init()
{
    title = "Example 14.2";

    vert = "./shader/s_14_2_blend_vert.glsl";
    frag = "./shader/s_14_2_blend_frag.glsl";

    model0 = "./res/model/pyr/pyr.obj";
}

void Painter_14_2::initWin(GLFWwindow* window)
{
    this->Painter::initWin(window);

    cameraX = 0.0f; cameraY = 0.3f; cameraZ = 4.0f;

    renderingProgram = Utils::createShaderProgram(vert, frag);

	currentLightPos = glm::vec3(0.0f, 2.3f, 4.0f);

    initVaoVbo(7);
    myModel = ImportedModel(model0);
    int index = setupVertices(myModel, 0);
    setupVertices(myTorus, index, true);
}

void Painter_14_2::display(GLFWwindow* window, double currentTime)
{
	glClear(GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(renderingProgram);

	mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix");
	projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");
	nLoc = glGetUniformLocation(renderingProgram, "norm_matrix");
	aLoc = glGetUniformLocation(renderingProgram, "alpha");
	fLoc = glGetUniformLocation(renderingProgram, "flipNormal");

	vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));

	// draw the torus
	mMat = glm::translate(glm::mat4(1.0f), glm::vec3(1.2f, 0.5f, -3.0f));
	mMat = glm::rotate(mMat, Utils::toRadians(35.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	mvMat = vMat * mMat;
	invTrMat = glm::transpose(glm::inverse(mvMat));

	currentLightPos = glm::vec3(lightLoc);
	installLights(renderingProgram, vMat, bMatAmb, bMatDif, bMatSpe, bMatShi);

	glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));
	glUniformMatrix4fv(nLoc, 1, GL_FALSE, glm::value_ptr(invTrMat));
	glProgramUniform1f(renderingProgram, aLoc, 1.0f);
	glProgramUniform1f(renderingProgram, fLoc, 1.0f);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[3]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[5]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glEnable(GL_CULL_FACE);
	glClear(GL_BACK);
	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[6]);
	glDrawElements(GL_TRIANGLES, myTorus.getNumIndices(), GL_UNSIGNED_INT, 0);

	// draw the pyramid
	mMat = glm::translate(glm::mat4(1.0f), glm::vec3(-0.1f, 0.3f, 0.3f));
	mMat = glm::rotate(mMat, Utils::toRadians(40.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	mMat = glm::rotate(mMat, Utils::toRadians(95.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	mvMat = vMat * mMat;
	invTrMat = glm::transpose(glm::inverse(mvMat));

	currentLightPos = glm::vec3(lightLoc);
	installLights(renderingProgram, vMat, matAmb, matDif, matSpe, matShi);

	glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));
	glUniformMatrix4fv(nLoc, 1, GL_FALSE, glm::value_ptr(invTrMat));
	glProgramUniform1f(renderingProgram, aLoc, 1.0f);
	glProgramUniform1f(renderingProgram, fLoc, 1.0f);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	// 2-pass rendering a transparent version of the pyramid
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendEquation(GL_FUNC_ADD);

	glEnable(GL_CULL_FACE);

	glCullFace(GL_FRONT);
	glProgramUniform1f(renderingProgram, aLoc, 0.3f);
	glProgramUniform1f(renderingProgram, fLoc, -1.0f);
	glDrawArrays(GL_TRIANGLES, 0, myModel.getNumVertices());

	glCullFace(GL_BACK);
	glProgramUniform1f(renderingProgram, aLoc, 0.7f);
	glProgramUniform1f(renderingProgram, fLoc, 1.0f);
	glDrawArrays(GL_TRIANGLES, 0, myModel.getNumVertices());

	glDisable(GL_BLEND);
}
