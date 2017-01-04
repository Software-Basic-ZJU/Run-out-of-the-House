# 计算机图形学：期末大程
- 一个简单的OpenGL密室逃生游戏
- An easy escape Game by OpenGL

## 场景描述
- 房子
- 门
    - 明门
    - 暗门（一道墙：封锁拿钥匙的房间，靠近自动移动开门）
- 电风扇
    - 不停的转
- 桌子
- 床
- 人 
    - 第一人称
    - 漫游
    - zoom to fit：摄像机上下看时fit到平视
- 钥匙
    - 位于橱柜顶端
    - 拿钥匙时，移动桌子动画，踩上桌子，拿到钥匙
- 橱柜

## 分工
- 老板：静态基础场景搭建
- 陈然：场景动画（门、风扇、移桌子）
- 永杰：材质、纹理、光照
- 旺泰：人物、漫游、碰撞检测
- ddl：1月8日


## 数据结构
### 父类：几何体
```class
class Geometry{
public:		
	bool hidden;							//是否隐藏
	GLfloat x, y, z;						//三维坐标
	GLfloat angle;							//旋转角度
	GLfloat rotX, rotY, rotZ;				//旋转所绕的向量

	Geometry(GLfloat x = 0, GLfloat y = 0, GLfloat z = 0);	//几何体构造
	
	void rotateX(GLfloat angle);							//绕x轴方向自旋转
	void rotateY(GLfloat angle);							//绕y轴方向自旋转
	void rotateZ(GLfloat angle);							//绕z轴方向自旋转
	void rotate(GLfloat angle,GLfloat x, GLfloat y, GLfloat z);			//绕自定义向量旋转
	void setPosition(GLfloat x, GLfloat y, GLfloat z);		//设置位置

	void setTexture();										//设置纹理
	void isHide(bool hidden);								//是否隐藏
};
//子类需要重新定义draw和render函数
```
### 子类：圆锥体
```class
class Cone:public Geometry{
private:
	GLfloat radius, height;			//半径，高度
	GLint slice;					//横向分片
	void drawCone();				//绘制单位圆锥
public:
	Cone(GLfloat radius = 1, GLfloat height = 1, GLint slice = 50,
		GLfloat x = 0, GLfloat y = 0, GLfloat z = 0);

	virtual void render();
};
```

### 子类：立方体
```
class Cubic:public Geometry{
private:
	static GLfloat cubic[8][3];					//单位立方体坐标点
	static GLint cubicIndex[6][4];				//各面顶点坐标索引
	GLfloat length, width, height;				//长宽高

	void drawCubic();
public:
	Cubic(GLfloat length, GLfloat width, GLfloat height,
		GLfloat x = 0, GLfloat y = 0, GLfloat z = 0);		

	virtual void render();											//渲染函数

};
```

### 子类：圆柱体
```
class Cylinder:public Geometry{
private:
	GLfloat radius, height;			//底面圆半径、圆柱高
	GLint slice;					//横向分片数
	void drawCylinder();			//绘制单位圆柱
public:
	Cylinder(GLfloat radius = 1, GLfloat height = 1,GLint slice = 50,
		GLfloat x = 0, GLfloat y = 0, GLfloat z = 0);	
	virtual void render();
};
```

### 子类：棱柱与棱台
```
// 仅支持凸多边形的棱柱棱台

// 底面各顶点坐标，传入时须平行于xOz平面!!!!!!!!!!!!!!!!!!!!!!!!
class Prism :public Geometry{
private:

	GLfloat **btmVertexArr;							//底面多边形各定点二维数组，按顺序传入
	GLfloat **topVertexArr;							//顶部多边形各定点二维数组，按顺序传入

	int vertNum;									//多边形边数,最大支持20边
	GLfloat height;									//长,宽,高
	GLfloat angleX, angleZ;							//往+X方向与+Z方向的倾斜角
	GLfloat scaleX = 1, scaleY = 1, scaleZ = 1;		//各方向缩放比例
	void drawPrism();								//绘制单位棱柱
public:
	// 必传参数:传入二维点阵数组,顶点个数
	// 若为棱台，则需要再传入顶面二维点阵数组
	// 若不传入顶面多边形，则默认与底面相同
	Prism(GLfloat btmVertexArr[][2], int vertNum, GLfloat height = 1,GLfloat topVertexArr[][2] = NULL,
		GLfloat angleX = 0, GLfloat angleZ = 0, GLfloat x = 0, GLfloat y = 0, GLfloat z = 0);

	void setScale(GLfloat scaleX, GLfloat scaleY, GLfloat scaleZ);

	virtual void render();
};
```

### 子类：球体
```
class Sphere:public Geometry{
private:
	void drawSphere();		//绘制单位球体
	GLfloat radius;			//半径
	GLint M, N;				//横纵向分块数
public:

	// M,N表示球的横纵向被切分为几块
	Sphere(GLfloat radius = 1, GLint M = 50, GLint N = 50,
		GLfloat x = 0, GLfloat y = 0, GLfloat z = 0);

	void setRadius(GLfloat radius);				//设置半径

	void setMspice(GLfloat M);					//设置横向切片数

	void setNspice(GLfloat N);					//设置纵向切片数

	void render();
};
```
