#version 430

in vec3 vNormal, vLightDir, vVertPos, vHalfVec;
in vec4 shadow_coord;
out vec4 fragColor;
 
struct PositionalLight
{	
	vec4 ambient, diffuse, specular;
	vec3 position;
};

struct Material
{	
	vec4 ambient, diffuse, specular;
	float shininess;
};

uniform vec4 globalAmbient;
uniform PositionalLight light;
uniform Material material;
uniform mat4 mv_matrix; 
uniform mat4 proj_matrix;
uniform mat4 norm_matrix;
uniform mat4 shadowMVP;
layout (binding=0) uniform sampler2DShadow shadowTex;


// 从shadow_coord返回距离（x，y）处的纹素的阴影深度值
// shadow_coord是阴影贴图中与正在渲染的当前像素相对应的位置
float lookup(float ox, float oy)
{ float t = textureProj(shadowTex,
    shadow_coord + vec4(ox * 0.001 * shadow_coord.w, oy * 0.001 * shadow_coord.w,
    -0.01, 0.0)); //第三个参数（-0.01）是用于消除阴影痤疮的偏移量
  return t;
}

void main(void)
{	
    float shadowFactor = 0.0;

	vec3 L = normalize(vLightDir);
	vec3 N = normalize(vNormal);
	vec3 V = normalize(-vVertPos);
	vec3 H = normalize(vHalfVec);
	
	// -----此部分生成一个4采样抖动的柔和阴影
    float swidth = 2.5;     //可调整的阴影扩散量
    // 根据glFragCoord mod 2生成4采样模式中的一个
    vec2 offset = mod(floor(gl_FragCoord.xy), 2.0) * swidth;
    shadowFactor += lookup(-1.5*swidth + offset.x, 1.5*swidth - offset.y);
    shadowFactor += lookup(-1.5*swidth + offset.x, -0.5*swidth - offset.y);
    shadowFactor += lookup( 0.5*swidth + offset.x, 1.5*swidth - offset.y);
    shadowFactor += lookup( 0.5*swidth + offset.x, -0.5*swidth - offset.y);
    shadowFactor = shadowFactor / 4.0; // shadowFactor是4个采样点的平均值

    // ----- 取消本节注释以生成64采样的高分辨率柔和阴影
    // float swidth = 2.5;     // 可调整的阴影扩散量
    // float endp = swidth*3.0 +swidth/2.0;
    // for (float m=-endp ; m<=endp ; m=m+swidth)
    // {   for (float n=-endp ; n<=endp ; n=n+swidth)
    //     {          shadowFactor += lookup(m,n);
    // }   }
    // shadowFactor = shadowFactor / 64.0;

    vec4 shadowColor = globalAmbient * material.ambient + light.ambient * material.ambient; 
    vec4 lightedColor = light.diffuse * material.diffuse * max(dot(L,N),0.0) 
                      + light.specular * material.specular 
                      * pow(max(dot(H,N),0.0),material.shininess*3.0); 

    fragColor = vec4((shadowColor.xyz + shadowFactor*(lightedColor.xyz)),1.0);
}
