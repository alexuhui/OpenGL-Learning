#include "painter_14_7_3d_texture_clouds.h"

void Painter_14_7::init()
{
    title = "Example 14.7";

    vert = "./shader/s_14_7_3d_texture_clouds_vert.glsl";
    frag = "./shader/s_14_7_3d_texture_clouds_frag.glsl";

	//3d纹理
	noiseTexPath = "./res/3dtex/clouds.3dtex";
}

void Painter_14_7::initWin(GLFWwindow* window)
{
	this->Painter::initWin(window);

	cameraX = 0.0f; cameraY = 2.0f; cameraZ = 10.0f;

	renderingProgram = Utils::createShaderProgram(vert, frag);

	currentLightPos = glm::vec3(-2.0f, 3.0f, 0.6f);
	texRot = glm::rotate(glm::mat4(1.0f), Utils::toRadians(20.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	stopwatchStart();

	initVaoVbo(4);
	stopwatch("initVaoVbo");

	setupVertices(halfSphere, 0);
	stopwatch("setupVertices");
	
	skyTexture = buildNoiseTexture();
	stopwatch("buildNoiseTexture");
}

void Painter_14_7::display(GLFWwindow* window, double currentTime)
{
	glClear(GL_DEPTH_BUFFER_BIT);
	glClearColor(0.5, 0.5, 0.5, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(renderingProgram);

	mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix");
	projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");
	dOffsetLoc = glGetUniformLocation(renderingProgram, "depth");

	vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));
	mMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	mMat = glm::scale(glm::mat4(1.0f), glm::vec3(4.0f, 4.0f, 4.0f));
	rotAmt += 0.0005f;
	mMat = glm::rotate(mMat, rotAmt, glm::vec3(0.0f, 1.0f, 0.0f));
	mvMat = vMat * mMat;

	depth += 0.0001f; if (depth >= 0.99f) depth = 0.01f;

	glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));
	glUniform1f(dOffsetLoc, depth);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_3D, skyTexture);

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  // FILL or LINE
	glDrawArrays(GL_TRIANGLES, 0, halfSphere.getNumIndices());

	//stopwatch("display");
}

void Painter_14_7::fillDataArray(GLubyte data[]) {
	for (int i = 0; i < noiseHeight; i++) {
		for (int j = 0; j < noiseWidth; j++) {
			for (int k = 0; k < noiseDepth; k++) {
				float brightness = 1.0f - (float)turbulence(i, j, k, 32) / 256.0f;

				float redPortion = brightness * 255.0f;
				float greenPortion = brightness * 255.0f;
				float bluePortion = 1.0f * 255.0f;

				int index = i * (noiseWidth * noiseHeight * 4) + j * (noiseHeight * 4) + k * 4;
				data[index] = (GLubyte)redPortion;
				data[index + 1] = (GLubyte)greenPortion;
				data[index + 2] = (GLubyte)bluePortion;
				data[index + 3] = (GLubyte)0;
			}
		}
	}
	stopwatch("fillDataArray");

	int size = noiseWidth * noiseHeight * noiseDepth * 4;
	Utils::save3DTexture(noiseTexPath, data, size, noiseHeight, noiseWidth, noiseDepth);
	stopwatch("save3DTexture");
}

double Painter_14_7::turbulence(double x, double y, double z, double size) {
	double value = 0.0, initialSize = size, cloudQuant;
	while (size >= 0.9) {
		value = value + smoothNoise(x / size, y / size, z / size) * size;
		size = size / 2.0;
	}
	cloudQuant = 110.0; // tunable quantity of clouds
	value = value / initialSize;
	value = 256.0 * logistic(value * 128.0 - cloudQuant);
	//value = 128.0 * value / initialSize;
	return value;
}

// 3D Noise Texture section
double Painter_14_7::smoothNoise(double x1, double y1, double z1) {
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

GLuint Painter_14_7::buildNoiseTexture() {
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

void Painter_14_7::generateNoise() {
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
