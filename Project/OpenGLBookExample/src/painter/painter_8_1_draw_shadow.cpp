#include "painter_8_1_draw_shadow.h"

void Painter_8_1::init()
{
    title = "Example 8.1";

    vert = "./shader/s_8_1_shadow_pass1_vert.glsl";
    frag = "./shader/s_8_1_shadow_pass1_frag.glsl";

	vert2 = "./shader/s_8_1_shadow_pass2_vert.glsl";
	frag2 = "./shader/s_8_1_shadow_pass2_frag.glsl";

    tex0 = "./res/model/shuttle/spstob_1.jpg";
    model0 = "./res/model/pyr/pyr.obj";
}

void Painter_8_1::initWin(GLFWwindow* window)
{
    this->Painter::initWin(window);

    cameraX = 0.0f, cameraY = 0.0f, cameraZ = 2.0f;

	renderingProgram1 = Utils::createShaderProgram(vert, frag);
	renderingProgram2 = Utils::createShaderProgram(vert2, frag2);

    texture = Utils::loadTexture(tex0);
	myModel = ImportedModel(model0);

    //initVaoVbo(5);
    /*setupVertices(myTorus, 0, true);
    setupVertices(myModel, 4);*/
	setupVertices();

	setupShadowBuffers(window);
}

void Painter_8_1::setupVertices()
{
	// pyramid definition

	int numPyramidVertices = myModel.getNumVertices();
	std::vector<glm::vec3> vert = myModel.getVertices();
	std::vector<glm::vec3> norm = myModel.getNormals();

	std::vector<float> pyramidPvalues;
	std::vector<float> pyramidNvalues;

	for (int i = 0; i < numPyramidVertices; i++) {
		pyramidPvalues.push_back((vert[i]).x);
		pyramidPvalues.push_back((vert[i]).y);
		pyramidPvalues.push_back((vert[i]).z);
		pyramidNvalues.push_back((norm[i]).x);
		pyramidNvalues.push_back((norm[i]).y);
		pyramidNvalues.push_back((norm[i]).z);
	}

	// torus definition

	int numTorusVertices = myTorus.getNumVertices();
	int numTorusIndices = myTorus.getNumIndices();
	std::vector<int> ind = myTorus.getIndices();
	vert = myTorus.getVertices();
	norm = myTorus.getNormals();

	std::vector<float> torusPvalues;
	std::vector<float> torusNvalues;

	for (int i = 0; i < numTorusVertices; i++) {
		torusPvalues.push_back(vert[i].x);
		torusPvalues.push_back(vert[i].y);
		torusPvalues.push_back(vert[i].z);
		torusNvalues.push_back(norm[i].x);
		torusNvalues.push_back(norm[i].y);
		torusNvalues.push_back(norm[i].z);
	}

	vao = new GLuint[1];
	vbo = new GLuint[5];

	glGenVertexArrays(1, vao);
	glBindVertexArray(vao[0]);
	glGenBuffers(5, vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, torusPvalues.size() * 4, &torusPvalues[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, pyramidPvalues.size() * 4, &pyramidPvalues[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, torusNvalues.size() * 4, &torusNvalues[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[3]);
	glBufferData(GL_ARRAY_BUFFER, pyramidNvalues.size() * 4, &pyramidNvalues[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[4]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, ind.size() * 4, &ind[0], GL_STATIC_DRAW);
}

void Painter_8_1::display(GLFWwindow* window, double currentTime)
{
	glClear(GL_DEPTH_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT);

	currentLightPos = glm::vec3(lightLoc);

	lightVmatrix = glm::lookAt(currentLightPos, origin, up);
	lightPmatrix = glm::perspective(Utils::toRadians(60.0f), aspect, 0.1f, 1000.0f);

	glBindFramebuffer(GL_FRAMEBUFFER, shadowBuffer);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, shadowTex, 0);

	//glDrawBuffer(GL_FRONT);
	glDrawBuffer(GL_NONE);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_POLYGON_OFFSET_FILL);	// for reducing
	//glPolygonOffset(2.0f, 4.0f);		//  shadow artifacts

	passOne();

	//glDisable(GL_POLYGON_OFFSET_FILL);	// artifact reduction, continued

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, shadowTex);

	glDrawBuffer(GL_FRONT);

	passTwo();
}

void Painter_8_1::passOne() {
	glUseProgram(renderingProgram1);

	// draw the torus

	mMat = glm::translate(glm::mat4(1.0f), torusLoc);
	mMat = glm::rotate(mMat, Utils::toRadians(25.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	shadowMVP1 = lightPmatrix * lightVmatrix * mMat;
	sLoc = glGetUniformLocation(renderingProgram1, "shadowMVP");
	glUniformMatrix4fv(sLoc, 1, GL_FALSE, glm::value_ptr(shadowMVP1));

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[4]);
	glDrawElements(GL_TRIANGLES, myTorus.getNumIndices(), GL_UNSIGNED_INT, 0);

	// draw the pyramid

	mMat = glm::translate(glm::mat4(1.0f), pyrLoc);
	mMat = glm::rotate(mMat, Utils::toRadians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	mMat = glm::rotate(mMat, Utils::toRadians(40.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	shadowMVP1 = lightPmatrix * lightVmatrix * mMat;
	glUniformMatrix4fv(sLoc, 1, GL_FALSE, glm::value_ptr(shadowMVP1));

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glDrawArrays(GL_TRIANGLES, 0, myModel.getNumVertices());
}

void Painter_8_1::passTwo() {
	glUseProgram(renderingProgram2);

	mvLoc = glGetUniformLocation(renderingProgram2, "mv_matrix");
	projLoc = glGetUniformLocation(renderingProgram2, "proj_matrix");
	nLoc = glGetUniformLocation(renderingProgram2, "norm_matrix");
	sLoc = glGetUniformLocation(renderingProgram2, "shadowMVP");

	// draw the torus
	vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraLoc.x, -cameraLoc.y, -cameraLoc.z));

	mMat = glm::translate(glm::mat4(1.0f), torusLoc);
	mMat = glm::rotate(mMat, Utils::toRadians(25.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	currentLightPos = glm::vec3(lightLoc);
	installLights(renderingProgram2, vMat, matAmb, matDif, matSpe, matShi);

	mvMat = vMat * mMat;
	invTrMat = glm::transpose(glm::inverse(mvMat));
	shadowMVP2 = bMat * lightPmatrix * lightVmatrix * mMat;

	glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));
	glUniformMatrix4fv(nLoc, 1, GL_FALSE, glm::value_ptr(invTrMat));
	glUniformMatrix4fv(sLoc, 1, GL_FALSE, glm::value_ptr(shadowMVP2));

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[4]);
	glDrawElements(GL_TRIANGLES, myTorus.getNumIndices(), GL_UNSIGNED_INT, 0);

	// draw the pyramid
	mMat = glm::translate(glm::mat4(1.0f), pyrLoc);
	mMat = glm::rotate(mMat, Utils::toRadians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	mMat = glm::rotate(mMat, Utils::toRadians(40.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	currentLightPos = glm::vec3(lightLoc);
	installLights(renderingProgram2, vMat, bMatAmb, bMatDif, bMatSpe, bMatShi);

	mvMat = vMat * mMat;
	invTrMat = glm::transpose(glm::inverse(mvMat));
	shadowMVP2 = bMat * lightPmatrix * lightVmatrix * mMat;

	glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));
	glUniformMatrix4fv(nLoc, 1, GL_FALSE, glm::value_ptr(invTrMat));
	glUniformMatrix4fv(sLoc, 1, GL_FALSE, glm::value_ptr(shadowMVP2));

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[3]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glDrawArrays(GL_TRIANGLES, 0, myModel.getNumVertices());
}

int Painter_8_1::getWidth()
{
    return 800;
}

int Painter_8_1::getHeight()
{
    return 800;
}
