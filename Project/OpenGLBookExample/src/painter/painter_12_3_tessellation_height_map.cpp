#include "painter_12_3_tessellation_height_map.h"

void Painter_12_3::init()
{
    title = "Example 12.3";

    vert = "./shader/s_12_3_tessellation_height_map_vert.glsl";
	tessC = "./shader/s_12_3_tessellation_height_map_tess_ctrl.glsl";
	tessE = "./shader/s_12_3_tessellation_height_map_tess_eval.glsl";
    frag = "./shader/s_12_3_tessellation_height_map_frag.glsl";

	tex0 = "./res/img/moon.jpg";
}

void Painter_12_3::initWin(GLFWwindow* window)
{
    this->Painter::initWin(window);

    cameraX = 0.0f, cameraY = 0.1f, cameraZ = 1.0f;

    renderingProgram = Utils::createShaderProgram(vert, tessC, tessE, frag);
	texture = Utils::loadTexture(tex0);

    initVaoVbo(1);
}

void Painter_12_3::display(GLFWwindow* window, double currentTime)
{
	glClear(GL_DEPTH_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(renderingProgram);

	vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));

	mMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	mMat = glm::rotate(mMat, Utils::toRadians(15.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	mvpMat = pMat * vMat * mMat;

	mvpLoc = glGetUniformLocation(renderingProgram, "mvp_matrix");

	glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(mvpMat));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glFrontFace(GL_CCW);

	glPatchParameteri(GL_PATCH_VERTICES, 1);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  // FILL or LINE
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // FILL or LINE
	glDrawArrays(GL_PATCHES, 0, 1);
}
