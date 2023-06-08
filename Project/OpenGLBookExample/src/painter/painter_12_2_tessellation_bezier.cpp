#include "painter_12_2_tessellation_bezier.h"

void Painter_12_2::init()
{
    title = "Example 12.2";

    vert = "./shader/s_12_2_tessellation_bezier_vert.glsl";
	tessC = "./shader/s_12_2_tessellation_bezier_tess_ctrl.glsl";
	tessE = "./shader/s_12_2_tessellation_bezier_tess_eval.glsl";
    frag = "./shader/s_12_2_tessellation_bezier_frag.glsl";

	tex0 = "./res/img/floor_color.jpg";
}

void Painter_12_2::initWin(GLFWwindow* window)
{
    this->Painter::initWin(window);

    cameraX = 0.0f, cameraY = 0.0f, cameraZ = 4.0f;
    renderingProgram = Utils::createShaderProgram(vert, tessC, tessE, frag);
	texture = Utils::loadTexture(tex0);
    initVaoVbo(1);
}

void Painter_12_2::display(GLFWwindow* window, double currentTime)
{
	glClear(GL_DEPTH_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(renderingProgram);

	vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));

	mMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	mMat = glm::rotate(mMat, Utils::toRadians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	mMat = glm::rotate(mMat, Utils::toRadians(100.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	mvpMat = pMat * vMat * mMat;

	mvpLoc = glGetUniformLocation(renderingProgram, "mvp_matrix");

	glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(mvpMat));

	GLuint timeLoc = glGetUniformLocation(renderingProgram, "time");
	glProgramUniform1f(renderingProgram, timeLoc, (float)currentTime);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glFrontFace(GL_CCW);

	glPatchParameteri(GL_PATCH_VERTICES, 16);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawArrays(GL_PATCHES, 0, 16);
}
