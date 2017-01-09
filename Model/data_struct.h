#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H

typedef struct tagVERTEX						// 创建Vertex顶点结构
{
	float xyz[3];							// 3D 坐标
	float normal[3];						//法向量
	float u, v;							// 纹理坐标
} VERTEX;	

typedef struct tagFACE						// 创建三角形或四边形结构
{
	bool bTriangle;//TRUE 为三角形，FALSE为四边形
	int index[4];//顶点的索引号
	float normal[3];	//面的法向量
} FACE;

typedef struct Vector3
{
	float x;
	float y;
	float z;
}VECTOR3;


#endif
