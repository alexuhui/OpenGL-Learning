#version 430
out vec4 fragColor;

uniform mat4 mvp_matrix;
in vec2 tes_out;
out vec4 color;
layout (binding = 0) uniform sampler2D tex_color;

void main(void)
{
	color = texture(tex_color, tes_out);
}
