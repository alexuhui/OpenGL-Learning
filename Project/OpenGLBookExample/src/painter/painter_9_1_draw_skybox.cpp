#include "painter_9_1_draw_skybox.h"

void Painter_9_1::init()
{
    title = "Example 9.1";

    vert = "./shader/s_5_1_draw_pyramid_texture_vert.glsl";
    frag = "./shader/s_5_1_draw_pyramid_texture_frag.glsl";

	tex0 = "./res/img/castleroof.jpg";
	texSkybox = "./res/skybox/lake_island.jpg";

	torLocX = 0.0f; torLocY = -0.75f; torLocZ = 0.0f;
	cameraX = 0.0f; cameraY = 0.0f; cameraZ = 5.0f;
}

void Painter_9_1::initWin(GLFWwindow* window)
{
	this->Painter::initWin(window);

    renderingProgram = Utils::createShaderProgram(vert, frag);

	mainTexture = Utils::loadTexture(tex0);
	skyboxTexture = Utils::loadTexture(texSkybox);

    initVaoVbo(6);
    setupVbo(vertexPositions, sizeof(vertexPositions), 0);
    setupVbo(cubeTextureCoord, sizeof(cubeTextureCoord), 1);
    setupVertices(myTorus, 2, true);
}

void Painter_9_1::display(GLFWwindow* window, double currentTime)
{
	glClear(GL_DEPTH_BUFFER_BIT);
	glClearColor(0.5, 0.5, 0.5, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	float s = sin(currentTime);
	float newCX = cameraX + s, newCY = cameraY + s, newCZ = cameraZ + s;
	vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-newCX, -newCY, -newCZ));

	// draw cube map
	glUseProgram(renderingProgram);
	// 天空盒跟随摄像机位置
	mMat = glm::translate(glm::mat4(1.0f), glm::vec3(newCX, newCY, newCZ));
	mvMat = vMat * mMat;

	mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix");
	projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");

	glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, skyboxTexture);

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);	// cube is CW, but we are viewing the inside
	glDisable(GL_DEPTH_TEST);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	//glEnable(GL_DEPTH_TEST);

	// draw scene (in this case it is just a torus
	glUseProgram(renderingProgram);

	mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix");
	projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");

	mMat = glm::translate(glm::mat4(1.0f), glm::vec3(torLocX, torLocY, torLocZ));
	mMat = glm::rotate(mMat, Utils::toRadians(15.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	mvMat = vMat * mMat;

	glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));

	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[3]);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mainTexture);

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glDisable(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[5]);
	glDrawElements(GL_TRIANGLES, myTorus.getNumIndices(), GL_UNSIGNED_INT, 0);
}