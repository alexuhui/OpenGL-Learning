#version 430

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;

out vec3 v_normal;
out vec3 vertex;
out vec2 tc; // uv 

uniform mat4 mv_matrix;
uniform mat4 proj_matrix;
uniform mat4 n_matrix;
layout (binding = 0) uniform samplerCube cube_map;
layout(binding = 1) uniform sampler2D samp;

void main(void)
{
	tc = texCoord;
	vertex = (mv_matrix * vec4(position,1.0)).xyz;
	v_normal = (n_matrix * vec4(normal,1.0)).xyz;
	gl_Position = proj_matrix * mv_matrix * vec4(position,1.0);
}
