#version 430

in vec2 tc;
in vec3 v_normal;
in vec3 vertex;
out vec4 fragColor;

uniform mat4 mv_matrix;
uniform mat4 proj_matrix;
uniform mat4 n_matrix;
layout (binding = 0) uniform samplerCube cube_map;
layout (binding = 1) uniform sampler2D samp;

void main(void)
{
	vec3 r = -reflect(normalize(-vertex), normalize(v_normal));
	vec4 mainColor = texture(samp, tc);

	fragColor = mix(mainColor, texture(cube_map, r), mainColor.x * 2.5f);
}