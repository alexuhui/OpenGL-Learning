#version 430

in vec3 vertEyeSpacePos;
in vec2 tc;
in float height;
out vec4 fragColor;

uniform mat4 mv_matrix;
uniform mat4 proj_matrix;
layout (binding=0) uniform sampler2D t;	// for texture
layout (binding=1) uniform sampler2D h;	// for height map

void main(void)
{	
	vec4 fogColor = vec4(0.7, 0.8, 0.9, 1.0);	// bluish gray
	float fogStart = 0.2;
	float fogEnd = 0.8;
	float heightEnd = 0.2;

	// the distance from the camera to the vertex in eye space is simply the length of a
    // vector to that vertex, because the camera is at (0,0,0) in eye space.
	float dist = length(vertEyeSpacePos.xyz);

	float heightFactor = clamp(heightEnd - height, 0.0, heightEnd) / heightEnd;
	float fogFactor = 1 - clamp((fogEnd-dist)/(fogEnd-fogStart), 0.0, 1.0);
	fragColor = mix(fogColor,(texture(t,tc)), 1 - fogFactor * heightFactor);
}
