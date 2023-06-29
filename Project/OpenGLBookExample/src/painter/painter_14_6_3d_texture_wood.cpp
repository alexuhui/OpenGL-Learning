#include "painter_14_6_3d_texture_wood.h"

void Painter_14_6::init()
{
    title = "Example 14.6";

    vert = "./shader/s_14_6_3d_texture_wood_vert.glsl";
    frag = "./shader/s_14_6_3d_texture_wood_frag.glsl";

	model0 = "./res/model/dolphinLowPoly/dolphinLowPoly.obj";

	//3d纹理
	noiseTexPath = "./res/3dtex/wood.3dtex";
}

void Painter_14_6::initWin(GLFWwindow* window)
{
	this->Painter::initWin(window);

	cameraX = 0.0f; cameraY = 0.0f; cameraZ = 1.7f;

	renderingProgram = Utils::createShaderProgram(vert, frag);
	dolphinObj = ImportedModel(model0);

	currentLightPos = glm::vec3(-2.0f, 3.0f, 0.6f);
	texRot = glm::rotate(glm::mat4(1.0f), Utils::toRadians(20.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	stopwatchStart();

	initVaoVbo(3);
	stopwatch("initVaoVbo");

	setupVertices(dolphinObj, 0);
	stopwatch("setupVertices");
	
	noiseTexture = buildNoiseTexture();
	stopwatch("buildNoiseTexture");
}

void Painter_14_6::display(GLFWwindow* window, double currentTime)
{
	glClear(GL_DEPTH_BUFFER_BIT);
	glClearColor(0.5, 0.5, 0.5, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(renderingProgram);

	mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix");
	projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");
	nLoc = glGetUniformLocation(renderingProgram, "norm_matrix");
	tLoc = glGetUniformLocation(renderingProgram, "texRot");

	vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));
	mMat = glm::translate(glm::mat4(1.0f), glm::vec3(-0.15f, 0.0f, 0.0f));
	mMat = glm::rotate(mMat, Utils::toRadians(50.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	mvMat = vMat * mMat;
	invTrMat = glm::transpose(glm::inverse(mvMat));
	installLights(renderingProgram, vMat, wdMatAmb, wdMatDif, wdMatSpe, wdMatShi);

	glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));
	glUniformMatrix4fv(nLoc, 1, GL_FALSE, glm::value_ptr(invTrMat));
	glUniformMatrix4fv(tLoc, 1, false, glm::value_ptr(texRot));

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_3D, noiseTexture);

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDrawArrays(GL_TRIANGLES, 0, dolphinObj.getNumVertices());

	//stopwatch("display");
}

void Painter_14_6::fillDataArray(GLubyte data[]) {
	double xyPeriod = 40.0;
	double turbPower = 0.1;
	double turbSize = 32.0;
	for (int i = 0; i < noiseHeight; i++) {
		for (int j = 0; j < noiseWidth; j++) {
			for (int k = 0; k < noiseDepth; k++) {
				double xValue = (i - (double)noiseHeight / 2.0) / (double)noiseHeight;
				double yValue = (j - (double)noiseWidth / 2.0) / (double)noiseWidth;
				double distValue = sqrt(xValue * xValue + yValue * yValue)
					+ turbPower * turbulence(i, j, k, turbSize) / 256.0;
				double sineValue = 128.0 * abs(sin(2.0 * xyPeriod * distValue * 3.14159));

				float redPortion = (float)(80 + (int)sineValue);
				float greenPortion = (float)(30 + (int)sineValue);
				float bluePortion = 0.0f;

				data[i * (noiseWidth * noiseHeight * 4) + j * (noiseHeight * 4) + k * 4 + 0] = (GLubyte)redPortion;
				data[i * (noiseWidth * noiseHeight * 4) + j * (noiseHeight * 4) + k * 4 + 1] = (GLubyte)greenPortion;
				data[i * (noiseWidth * noiseHeight * 4) + j * (noiseHeight * 4) + k * 4 + 2] = (GLubyte)bluePortion;
				data[i * (noiseWidth * noiseHeight * 4) + j * (noiseHeight * 4) + k * 4 + 3] = (GLubyte)255;
			}
		}
	}
	stopwatch("fillDataArray");

	int size = noiseWidth * noiseHeight * noiseDepth * 4;
	Utils::save3DTexture(noiseTexPath, data, size, noiseHeight, noiseWidth, noiseDepth);
	stopwatch("save3DTexture");
}

double Painter_14_6::turbulence(double x, double y, double z, double size) {
	double value = 0.0, initialSize = size;
	while (size >= 0.9) {
		value = value + smoothNoise(x / size, y / size, z / size) * size;
		size = size / 2.0;
	}
	value = 128.0 * value / initialSize;
	return value;
}

// 3D Noise Texture section
double Painter_14_6::smoothNoise(double x1, double y1, double z1) {
	//get fractional part of x, y, and z
	double fractX = x1 - (int)x1;
	double fractY = y1 - (int)y1;
	double fractZ = z1 - (int)z1;

	//neighbor values
	int x2 = ((int)x1 + noiseWidth + 1) % noiseWidth;
	int y2 = ((int)y1 + noiseHeight + 1) % noiseHeight;
	int z2 = ((int)z1 + noiseDepth + 1) % noiseDepth;

	//smooth the noise by interpolating
	double value = 0.0;
	value += (1 - fractX) * (1 - fractY) * (1 - fractZ) * noise[(int)x1][(int)y1][(int)z1];
	value += (1 - fractX) * fractY * (1 - fractZ) * noise[(int)x1][(int)y2][(int)z1];
	value += fractX * (1 - fractY) * (1 - fractZ) * noise[(int)x2][(int)y1][(int)z1];
	value += fractX * fractY * (1 - fractZ) * noise[(int)x2][(int)y2][(int)z1];

	value += (1 - fractX) * (1 - fractY) * fractZ * noise[(int)x1][(int)y1][(int)z2];
	value += (1 - fractX) * fractY * fractZ * noise[(int)x1][(int)y2][(int)z2];
	value += fractX * (1 - fractY) * fractZ * noise[(int)x2][(int)y1][(int)z2];
	value += fractX * fractY * fractZ * noise[(int)x2][(int)y2][(int)z2];

	return value;
}

GLuint Painter_14_6::buildNoiseTexture() {
	GLuint textureID;
	GLubyte* data = new GLubyte[noiseHeight * noiseWidth * noiseDepth * 4];

	stopwatchStart();
	bool read = Utils::read3DTexture(noiseTexPath, data, noiseHeight, noiseWidth, noiseDepth);
	stopwatch("read DataArray");
	if (!read)
	{
		generateNoise();
		stopwatch("generateNoise");
		fillDataArray(data);
	}

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_3D, textureID);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexStorage3D(GL_TEXTURE_3D, 1, GL_RGBA8, noiseWidth, noiseHeight, noiseDepth);
	glTexSubImage3D(GL_TEXTURE_3D, 0, 0, 0, 0, noiseWidth, noiseHeight, noiseDepth, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8_REV, data);

	return textureID;
}

void Painter_14_6::generateNoise() {
	noise = new double** [noiseHeight];
	for (int x = 0; x < noiseHeight; x++) {
		noise[x] = new double* [noiseWidth];
		for (int y = 0; y < noiseWidth; y++) {
			noise[x][y] = new double[noiseDepth];
			for (int z = 0; z < noiseDepth; z++) {
				noise[x][y][z] = (double)rand() / (RAND_MAX + 1.0);
			}
		}
	}
}
