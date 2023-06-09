#include "painter_12_6_tessellation_height_map_lod.h"

void Painter_12_6::init()
{
    title = "Example 12.6";

    vert = "./shader/s_12_6_tessellation_height_map_lod_vert.glsl";
	tessC = "./shader/s_12_6_tessellation_height_map_lod_tess_ctrl.glsl";
	tessE = "./shader/s_12_6_tessellation_height_map_lod_tess_eval.glsl";
    frag = "./shader/s_12_6_tessellation_height_map_lod_frag.glsl";

	tex0 = "./res/img/square_moon/squareMoonMap.jpg";
	tex_height = "./res/img/square_moon/squareMoonBump.jpg";
}

void Painter_12_6::initWin(GLFWwindow* window)
{
    this->Painter::initWin(window);

    cameraX = 0.0f, cameraY = 0.0f, cameraZ = 0.7f;
	currentLightPos = glm::vec3(0.0f, 0.1f, 0.2f);

    renderingProgram = Utils::createShaderProgram(vert, tessC, tessE, frag);
	texture = Utils::loadTexture(tex0);
	heightMap = Utils::loadTexture(tex_height);

    initVaoVbo(1);
}

void Painter_12_6::display(GLFWwindow* window, double currentTime)
{
	glClear(GL_DEPTH_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(renderingProgram);

	vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));
	cameraZ += transDir * 0.05f;
	if (cameraZ > 0.9f) transDir = -0.05f;
	if (cameraZ < 0.3f) transDir = 0.05f;

	mMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	mMat = glm::rotate(mMat, Utils::toRadians(20.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	mvpMat = pMat * vMat * mMat;

	mvpLoc = glGetUniformLocation(renderingProgram, "mvp_matrix");

	glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(mvpMat));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, heightMap);

	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);

	glPatchParameteri(GL_PATCH_VERTICES, 4);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArraysInstanced(GL_PATCHES, 0, 4, 64 * 64);
}
