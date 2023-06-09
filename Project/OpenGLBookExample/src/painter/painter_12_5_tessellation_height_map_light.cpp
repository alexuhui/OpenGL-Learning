#include "painter_12_5_tessellation_height_map_light.h"

void Painter_12_5::init()
{
    title = "Example 12.5";

    vert = "./shader/s_12_5_tessellation_height_map_light_vert.glsl";
	tessC = "./shader/s_12_5_tessellation_height_map_light_tess_ctrl.glsl";
	tessE = "./shader/s_12_5_tessellation_height_map_light_tess_eval.glsl";
    frag = "./shader/s_12_5_tessellation_height_map_light_frag.glsl";

	tex0 = "./res/img/square_moon/squareMoonMap.jpg";
	tex_normal = "./res/img/square_moon/squareMoonNormal.jpg";
	tex_height = "./res/img/square_moon/squareMoonBump.jpg";
}

void Painter_12_5::initWin(GLFWwindow* window)
{
    this->Painter::initWin(window);

    cameraX = 0.0f, cameraY = 0.0f, cameraZ = 0.5f;
	currentLightPos = glm::vec3(0.0f, 0.1f, 0.2f);

    renderingProgram = Utils::createShaderProgram(vert, tessC, tessE, frag);
	texture = Utils::loadTexture(tex0);
	normalMap = Utils::loadTexture(tex_normal);
	heightMap = Utils::loadTexture(tex_height);

    initVaoVbo(1);
}

void Painter_12_5::display(GLFWwindow* window, double currentTime)
{
	glClear(GL_DEPTH_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(renderingProgram);

	currentLightPos.x += lightMovement;
	if (currentLightPos.x > 0.8) lightMovement = -0.01f;
	else if (currentLightPos.x < -0.8) lightMovement = 0.01f;

	mvpLoc = glGetUniformLocation(renderingProgram, "mvp_matrix");
	mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix");
	projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");
	nLoc = glGetUniformLocation(renderingProgram, "norm_matrix");

	vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));

	mMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	mMat = glm::rotate(mMat, Utils::toRadians(20.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	mvMat = vMat * mMat;
	mvpMat = pMat * vMat * mMat;
	invTrMat = glm::transpose(glm::inverse(mvMat));

	installLights(renderingProgram, vMat, sMatAmb, sMatDif, sMatSpe, bMatShi);

	glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(mvpMat));
	glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));
	glUniformMatrix4fv(nLoc, 1, GL_FALSE, glm::value_ptr(invTrMat));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, heightMap);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, normalMap);

	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);

	glPatchParameteri(GL_PATCH_VERTICES, 4);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArraysInstanced(GL_PATCHES, 0, 4, 64 * 64);
}
