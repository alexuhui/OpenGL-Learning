#include "painter_13_4_geometry_add.h"

void Painter_13_4::init()
{
    title = "Example 13.4";

    vert = "./shader/s_13_4_geometry_add_vert.glsl";
    frag = "./shader/s_13_4_geometry_add_frag.glsl";
    geom = "./shader/s_13_4_geometry_add_geom.glsl";
}

void Painter_13_4::initWin(GLFWwindow* window)
{
    this->Painter::initWin(window);

    cameraX = 0.0f, cameraY = 0.0f, cameraZ = 0.0f;

    renderingProgram = Utils::createShaderProgram(vert, geom, frag);

    initVaoVbo(4);
    texture = Utils::loadTexture(tex0);
    setupVertices(myTorus, 0, true);
}