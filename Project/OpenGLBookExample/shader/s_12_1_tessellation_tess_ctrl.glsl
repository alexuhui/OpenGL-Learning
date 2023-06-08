#version 430

uniform mat4 mvp_matrix;
layout (vertices = 1) out;

void main(void)
{	
	float r = 2;
	gl_TessLevelOuter[0] = 6 * r;
	gl_TessLevelOuter[2] = 6 * r;
	gl_TessLevelOuter[1] = 6 * r;
	gl_TessLevelOuter[3] = 6 * r;
	gl_TessLevelInner[0] = 12 * r;
	gl_TessLevelInner[1] = 12 * r;
}