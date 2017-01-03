#include "Geometry.h"

// ��֧��͹����ε�����

// ������������꣬����ʱ��ƽ����xOzƽ��!!!!!!!!!!!!!!!!!!!!!!!!
class Prism :public Geometry{
private:
	GLfloat **vertexArr;							//�������θ������ά���飬��˳����
	int vertNum;									//����α���,���֧��20��
	GLfloat height;									//��,��,��
	GLfloat angleX, angleZ;							//��+X������+Z�������б��
	GLfloat scaleX = 1, scaleY = 1, scaleZ = 1;		//���������ű���
	void drawPrism();								//���Ƶ�λ����
public:
	// �ش�����:�����ά��������,�������
	Prism(GLfloat vertexArr[][2], int vertNum, GLfloat height = 1, GLfloat angleX = 0, GLfloat angleZ = 0,
		GLfloat x = 0, GLfloat y = 0, GLfloat z = 0);

	void setScale(GLfloat scaleX, GLfloat scaleY, GLfloat scaleZ);

	void render();
};