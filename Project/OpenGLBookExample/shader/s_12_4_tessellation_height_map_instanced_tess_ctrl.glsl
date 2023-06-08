#version 430

uniform mat4 mvp_matrix;
layout (binding = 0) uniform sampler2D tex_color;
in vec2 tc[ ];
out vec2 tcs_out[ ];

layout (vertices = 1) out;

void main(void)
{	
	float TL = 32;
	if (gl_InvocationID == 0)
	{
		gl_TessLevelOuter[0] = TL;
		gl_TessLevelOuter[2] = TL;
		gl_TessLevelOuter[1] = TL;
		gl_TessLevelOuter[3] = TL;
		gl_TessLevelInner[0] = TL;
		gl_TessLevelInner[1] = TL;
	}

	tcs_out[gl_InvocationID] = tc[gl_InvocationID];
	gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
}