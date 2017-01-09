#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H

typedef struct tagVERTEX						// ����Vertex����ṹ
{
	float xyz[3];							// 3D ����
	float normal[3];						//������
	float u, v;							// ��������
} VERTEX;	

typedef struct tagFACE						// ���������λ��ı��νṹ
{
	bool bTriangle;//TRUE Ϊ�����Σ�FALSEΪ�ı���
	int index[4];//�����������
	float normal[3];	//��ķ�����
} FACE;

typedef struct Vector3
{
	float x;
	float y;
	float z;
}VECTOR3;


#endif
