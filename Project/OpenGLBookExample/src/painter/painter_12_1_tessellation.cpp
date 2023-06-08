#include "painter_12_1_tessellation.h"

void Painter_12_1::init()
{
    title = "Example 10.4";

    vert = "./shader/s_12_1_tessellation_vert.glsl";
	tessC = "./shader/s_12_1_tessellation_tessC.glsl";
	tessE = "./shader/s_12_1_tessellation_tessE.glsl";
    frag = "./shader/s_12_1_tessellation_frag.glsl";
}

void Painter_12_1::initWin(GLFWwindow* window)
{
    this->Painter::initWin(window);

    cameraX = 0.0f, cameraY = 0.0f, cameraZ = 2.0f;
	currentLightPos = glm::vec3(3.0f, 2.0f, 3.0f);

    renderingProgram = Utils::createShaderProgram(vert, tessC, tessE, frag);

    initVaoVbo(1);
}

void Painter_12_1::display(GLFWwindow* window, double currentTime)
{
	glClear(GL_DEPTH_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(renderingProgram);

	vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));

	mMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	mMat = glm::rotate(mMat, Utils::toRadians(35.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	mvpMat = pMat * vMat * mMat;

	mvpLoc = glGetUniformLocation(renderingProgram, "mvp_matrix");

	glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(mvpMat));

	glFrontFace(GL_CCW);

	glPatchParameteri(GL_PATCH_VERTICES, 1);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  // FILL or LINE
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // FILL or LINE
	glDrawArrays(GL_PATCHES, 0, 1);
}
