#version 430
out vec4 fragColor;

uniform mat4 mvp_matrix;	 

void main(void)
{
	fragColor = vec4(0.9, 0.5, 0.5, 1.0);
}
