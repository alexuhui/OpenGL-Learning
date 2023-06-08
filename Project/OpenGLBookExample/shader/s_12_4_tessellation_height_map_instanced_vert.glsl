#version 430

uniform mat4 mvp_matrix;
layout (binding = 0) uniform sampler2D tex_color;
out vec2 tc;

void main(void)
{
	vec2 patchTexCoords[ ] = vec2[ ] (vec2(0,0), vec2(1,0), vec2(0,1), vec2(1,1));

	// 基于当前是哪个实例计算出坐标偏移量
	int x = gl_InstanceID % 64;
	int y = gl_InstanceID / 64;

	// 纹理坐标被分配进64个补丁中，并归一化到[0..1]。翻转Y轴坐标
	tc = vec2( (x+patchTexCoords[gl_VertexID].x) / 64.0, (63 - y+patchTexCoords[gl_VertexID].y) / 64.0);

	// 顶点位置和纹理坐标相同，只是它的取值范围从-0.5到+0.5
	gl_Position = vec4(tc.x - 0.5, 0.0, (1.0 - tc.y) - 0.5, 1.0);         // 并且将Y轴坐标翻转回来
}
