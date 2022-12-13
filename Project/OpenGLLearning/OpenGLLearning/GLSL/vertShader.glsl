#version 430


layout (location = 0) in vec3 position;

//uniform mat4 mv_matrix;
uniform mat4 m_matrix;
uniform mat4 v_matrix;
uniform mat4 proj_matrix;

uniform float tf;

out vec4 varyingColor;

mat4 buildRotateX(float rad);
mat4 buildRotateY(float rad);
mat4 buildRotateZ(float rad);
mat4 buildTranslate(float x, float y, float z);

void main(void)
{ 
	float i = gl_InstanceID + tf;
	float a = sin(203.0 * i / 8000.0) * 203.0;
	float b = sin(301.0 * i / 4001.0) * 201.0;
	float c = sin(400.0 * i / 6003.0) * 205.0;

//    float a = sin(2.0 * i) * 8.0;
//    float b = sin(3.0 * i) * 8.0;
//    float c = sin(4.0 * i) * 8.0;

	mat4 localRotX = buildRotateX(1000*i);
	mat4 localRotY = buildRotateY(1000*i);
	mat4 localRotZ = buildRotateZ(1000*i);
	mat4 localTrans = buildTranslate(a, b, c);

	mat4 newM_matrix = m_matrix * localTrans;// * localRotX * localRotY * localRotZ;
	mat4 mv_matrix = v_matrix * newM_matrix;

	vec4 pos = vec4(position, 1.0);
	gl_Position = proj_matrix * mv_matrix * pos;
	varyingColor = pos * 0.5 + vec4(0.5, 0.5, 0.5, 0.5);
}


// 构建并返回平移矩阵
mat4 buildTranslate(float x, float y, float z)
{ mat4 trans = mat4(1.0, 0.0, 0.0, 0.0, 
                    0.0, 1.0, 0.0, 0.0, 
                    0.0, 0.0, 1.0, 0.0, 
                    x, y, z, 1.0 ); 
  return trans;
} 

// 构建并返回绕X轴的旋转矩阵
mat4 buildRotateX(float rad)
{ mat4 xrot = mat4(1.0, 0.0, 0.0, 0.0, 
                   0.0, cos(rad), -sin(rad), 0.0, 
                   0.0, sin(rad), cos(rad), 0.0, 
                   0.0, 0.0, 0.0, 1.0 ); 
  return xrot;
}

// 构建并返回绕Y轴的旋转矩阵
mat4 buildRotateY(float rad)
{ mat4 yrot = mat4(cos(rad), 0.0, sin(rad), 0.0, 
                   0.0, 1.0, 0.0, 0.0, 
                   -sin(rad), 0.0, cos(rad), 0.0, 
                   0.0, 0.0, 0.0, 1.0 ); 
  return yrot;
}

// 构建并返回绕Z轴的旋转矩阵
mat4 buildRotateZ(float rad)
{ mat4 zrot = mat4(cos(rad), -sin(rad), 0.0, 0.0, 
                   sin(rad), cos(rad), 0.0, 0.0, 
                   0.0, 0.0, 1.0, 0.0, 
                   0.0, 0.0, 0.0, 1.0 ); 
  return zrot;
}

// 构建并返回缩放矩阵
mat4 buildScale(float x, float y, float z)
{ mat4 scale = mat4(x, 0.0, 0.0, 0.0, 
                    0.0, y, 0.0, 0.0, 
                    0.0, 0.0, z, 0.0, 
                    0.0, 0.0, 0.0, 1.0 ); 
  return scale;
}