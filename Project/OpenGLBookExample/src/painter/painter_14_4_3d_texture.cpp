#include "painter_14_4_3d_texture.h"

void Painter_14_4::init()
{
    title = "Example 14.4";

    vert = "./shader/s_14_4_3d_texture_vert.glsl";
    frag = "./shader/s_14_4_3d_texture_frag.glsl";

	model0 = "./res/model/dolphinLowPoly/dolphinLowPoly.obj";
}

void Painter_14_4::initWin(GLFWwindow* window)
{
    this->Painter::initWin(window);

    cameraX = 0.0f; cameraY = 0.0f; cameraZ = 2.0f;

    renderingProgram = Utils::createShaderProgram(vert, frag);
	dolphinObj = ImportedModel(model0);

	tex3Dpattern = new double** [texHeight];
	for (int i = 0; i < texHeight; i++)
	{
		tex3Dpattern[i] = new double* [texWidth];
		for (int j = 0; j < texWidth; j++)
		{
			tex3Dpattern[i][j] = new double[texDepth];
		}
	}

    initVaoVbo(3);
    setupVertices(dolphinObj, 0);
	generate3Dpattern();
	stripesTexture = build3DTexture();
}

void Painter_14_4::display(GLFWwindow* window, double currentTime)
{
	glClear(GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(renderingProgram);

	mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix");
	projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");

	vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));
	mMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	mMat = glm::rotate(mMat, Utils::toRadians(15.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	mMat = glm::rotate(mMat, Utils::toRadians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	mvMat = vMat * mMat;

	glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_3D, stripesTexture);

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDrawArrays(GL_TRIANGLES, 0, dolphinObj.getNumVertices());
}

void Painter_14_4::fillDataArray(GLubyte data[]) {
	for (int i = 0; i < texHeight; i++) {
		for (int j = 0; j < texWidth; j++) {
			for (int k = 0; k < texDepth; k++) {
				if (tex3Dpattern[i][j][k] == 1.0) {
					// yellow color
					data[i * (texWidth * texHeight * 4) + j * (texHeight * 4) + k * 4 + 0] = (GLubyte)255; //red
					data[i * (texWidth * texHeight * 4) + j * (texHeight * 4) + k * 4 + 1] = (GLubyte)255; //green
					data[i * (texWidth * texHeight * 4) + j * (texHeight * 4) + k * 4 + 2] = (GLubyte)0; //blue
					data[i * (texWidth * texHeight * 4) + j * (texHeight * 4) + k * 4 + 3] = (GLubyte)0; //alpha
				}
				else {
					// blue color
					data[i * (texWidth * texHeight * 4) + j * (texHeight * 4) + k * 4 + 0] = (GLubyte)0; //red
					data[i * (texWidth * texHeight * 4) + j * (texHeight * 4) + k * 4 + 1] = (GLubyte)0; //green
					data[i * (texWidth * texHeight * 4) + j * (texHeight * 4) + k * 4 + 2] = (GLubyte)255; //blue
					data[i * (texWidth * texHeight * 4) + j * (texHeight * 4) + k * 4 + 3] = (GLubyte)0; //alpha
				}
			}
		}
	}
}

int Painter_14_4::build3DTexture() {
	GLuint textureID;
	GLubyte* data = new GLubyte[texHeight * texWidth * texDepth * 4];

	fillDataArray(data);

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_3D, textureID);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexStorage3D(GL_TEXTURE_3D, 1, GL_RGBA8, texWidth, texHeight, texDepth);
	glTexSubImage3D(GL_TEXTURE_3D, 0, 0, 0, 0, texWidth, texHeight, texDepth, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8_REV, data);

	return textureID;
}

void Painter_14_4::generate3Dpattern() {
	for (int x = 0; x < texHeight; x++) {
		for (int y = 0; y < texWidth; y++) {
			for (int z = 0; z < texDepth; z++) {
				if ((y / 10) % 2 == 0)
					tex3Dpattern[x][y][z] = 0.0;
				else
					tex3Dpattern[x][y][z] = 1.0;
			}
		}
	}
}
