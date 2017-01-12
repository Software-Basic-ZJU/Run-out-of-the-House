#pragma once
#include "gl/glut.h"
#define RadiusOfPerson 1.0f
#define StepLength 0.2f
#ifndef PI
#define PI 3.1415926536f
#endif
#define ZERO 0.000001f

typedef enum { left_ward, right_ward, front, back }direction;

struct point {
	float x;
	float z;
	point(float _x, float _y) :x(_x), z(_y) { }
};

struct localVector {
	float x;
	float z;
	localVector(float _x, float _y) :x(_x), z(_y) { }
};
	//bool outCollisionToSquare(float *eye, float *center, point &p1, point &p3);
	//bool outCollisionToCircle(float *eye, float *center, point &o, float r);
	//bool inCollisionToSquare(float *eye, float *center, point &p1, point &p2, point &p3, point &p4);
	int nearDoor(point eyePos, point centerPos);
	bool CollosionTest(float x, float z, bool door1_open, bool door2_open, bool door3_open, bool wall_open);
	void move(const float *eye, const float *center, float *eye_next, float *center_next, direction dir);
	void rotate(const float *eye, const float *center, float *eye_next, float *center_next, direction dir);
	int myRoonNo(float x, float z);
class Person
{
private:



public:

	Person();
	~Person() {};
	
	//void inCollisionToCircle(float *eye, float *center, point &o, float r);
};

