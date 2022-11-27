#version 430


layout (location = 0) in vec3 position;

uniform mat4 mv_matrix;
uniform mat4 proj_matrix;

out vec4 varyingColor;

void main(void)
{ 
	vec4 pos = vec4(position, 1.0);
	gl_Position = proj_matrix * mv_matrix * pos;
	varyingColor = pos * 0.5 + vec4(0.5, 0.5, 0.5, 0.5);
}