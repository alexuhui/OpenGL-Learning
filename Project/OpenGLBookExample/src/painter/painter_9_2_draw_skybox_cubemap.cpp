#include "painter_9_2_draw_skybox_cubemap.h"

void Painter_9_2::init()
{
    title = "Example 9.2";

    vert = "./shader/s_5_1_draw_pyramid_texture_vert.glsl";
    frag = "./shader/s_5_1_draw_pyramid_texture_frag.glsl";

	vert_cubemap = "./shader/s_9_2_cubemap_vert.glsl";
	frag_cubemap = "./shader/s_9_2_cubemap_frag.glsl";

	tex0 = "./res/img/castleroof.jpg";
	texSkybox = "./res/skybox/cube_map/storm_clouds";

	torLocX = 0.0f; torLocY = -0.75f; torLocZ = 0.0f;
	cameraX = 0.0f; cameraY = 0.0f; cameraZ = 5.0f;
}

void Painter_9_2::initWin(GLFWwindow* window)
{
	this->Painter::initWin(window);

	renderingProgram = Utils::createShaderProgram(vert, frag);
	renderingProgram2 = Utils::createShaderProgram(vert_cubemap, frag_cubemap);

	mainTexture = Utils::loadTexture(tex0);
	skyboxTexture = Utils::loadCubeMap(texSkybox);

    initVaoVbo(5);
    setupVbo(vertexPositions, sizeof(vertexPositions), 0);
    setupVertices(myTorus, 1, true);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
}

void Painter_9_2::display(GLFWwindow* window, double currentTime)
{
	glClear(GL_DEPTH_BUFFER_BIT);
	glClearColor(0.5, 0.5, 0.5, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	float s = sin(currentTime);
	float newCX = cameraX + s, newCY = cameraY + s, newCZ = cameraZ + s;
	vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-newCX, -newCY, -newCZ));
	vMat *= rotate(glm::mat4(1.0f), 5.0f * s, glm::vec3(1.0f, 1.0f, 1.0f));

	// draw cube map
	glUseProgram(renderingProgram2);

	vLoc = glGetUniformLocation(renderingProgram2, "v_matrix");
	glUniformMatrix4fv(vLoc, 1, GL_FALSE, glm::value_ptr(vMat));

	projLoc = glGetUniformLocation(renderingProgram2, "p_matrix");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTexture);

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

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mainTexture);

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glDisable(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[4]);
	glDrawElements(GL_TRIANGLES, myTorus.getNumIndices(), GL_UNSIGNED_INT, 0);
}