#version 430

in vec3 varyingNormal;
in vec3 varyingLightDir;
in vec3 varyingVertPos;

out vec4 fragColor;

struct PositionalLight
{	vec4 ambient;  
	vec4 diffuse;  
	vec4 specular;  
	vec3 position;
};

struct Material
{	vec4 ambient;  
	vec4 diffuse;  
	vec4 specular;  
	float shininess;
};

uniform vec4 globalAmbient;
uniform PositionalLight light;
uniform Material material;
uniform mat4 mv_matrix;	 
uniform mat4 proj_matrix;
uniform mat4 norm_matrix;

void main(void)
{	
	
	 vec3 N;
	// 添加如下代码以扰乱传入的法向量
	float a = 0.25;  // a 控制凸起的高度
	float b = 50.0; // b 控制凸起的宽度
	float x = varyingVertPos.x;
	float y = varyingVertPos.y;
	float z = varyingVertPos.z;
	N.x = varyingNormal.x + a*sin(b*x);   // 使用正弦函数扰乱传入法向量
	N.y = varyingNormal.y + a*sin(b*y);
	N.z = varyingNormal.z + a*sin(b*z);
	N = normalize(N);

	// normalize the light, normal, and view vectors:
	vec3 L = normalize(varyingLightDir);
	//vec3 N = normalize(varyingNormal);
	vec3 V = normalize(-varyingVertPos);
	
	// compute light reflection vector, with respect N:
	vec3 R = normalize(reflect(-L, N));
	
	// get the angle between the light and surface normal:
	float cosTheta = dot(L,N);
	
	// angle between the view vector and reflected light:
	float cosPhi = dot(V,R);

	// compute ADS contributions (per pixel):
	vec3 ambient = ((globalAmbient * material.ambient) + (light.ambient * material.ambient)).xyz;
	vec3 diffuse = light.diffuse.xyz * material.diffuse.xyz * max(cosTheta,0.0);
	vec3 specular = light.specular.xyz * material.specular.xyz * pow(max(cosPhi,0.0), material.shininess);
	
	fragColor = vec4((ambient + diffuse + specular), 1.0);
}
