#include<stdio.h>  
#include <math.h>
#include "Person.h"

extern float center[3];
extern float eye[3];


float min(float x, float y)
{
	return x < y ? x : y;
}

float max(float x, float y)
{
	return x > y ? x : y;
}

Person::Person()
{
	/*center[0] = 0;
	center[1] = 0;
	center[2] = 35;
	eye[0] = 0;
	eye[1] = 0;
	eye[2] = 40;*/
}
bool FloatEqual(float a, float b)
{
	return a - b<ZERO && a - b>-ZERO;
}
float flabs(float x)
{
	return x > 0 ? x : -x;
}
float distanceBetweenPoints(point &p1, point &p2)
{
	return sqrtf((p1.x - p2.x)*(p1.x - p2.x) + (p1.z - p2.z)*(p1.z - p2.z));
}
bool JoinCircleLine(point &o, float r, point &p1, point &p2)
{
	float f1;
	if (FloatEqual(p1.x, p2.x))
		f1 = flabs(p1.x - o.x);
	else if (FloatEqual(p1.z, p2.z))
		f1 = flabs(p1.z - o.z);
//	printf("000%f %f\n", f1, r);
	if (f1 > r) {// || FloatEqual(f1, r)
//		printf("111%f %f\n", f1,r);
		return false;
	}
		

	float f2 = distanceBetweenPoints(o, p1);
	float f3 = distanceBetweenPoints(o, p2);
//	printf("aaa%f %f %f\n", f2,f3, r);
	if (f2 < r || f3 < r) {
//		printf("222%f %f %f\n", f2,f3,r);
		return true;
	}
		
	// || FloatEqual(max(p1.z, p2.z), o.z) || FloatEqual(min(p1.z, p2.z), o.z)   || FloatEqual(max(p1.x, p2.x), o.x) || FloatEqual(min(p1.x, p2.x), o.x)
	if (FloatEqual(p1.x, p2.x)) {
		if (max(p1.z, p2.z) < o.z || min(p1.z, p2.z) > o.z) {
	//		printf("333%f %f %f %f %f %f\n", p1.x, p1.z, p2.x, p2.z, o.x, o.z);
			return false;
		}
			
		else {
	//		printf("444%f %f %f %f %f %f\n", p1.x, p1.z, p2.x, p2.z, o.x, o.z);
			return true;
		}
			
	}
	else if (FloatEqual(p1.z, p2.z)) {
		if (max(p1.x, p2.x) < o.x || min(p1.x, p2.x) > o.x) {
	//		printf("555%f %f %f %f %f %f\n", p1.x, p1.z, p2.x, p2.z, o.x, o.z);
			return false;
		}
		else {
	//		printf("666%f %f %f %f %f %f\n",p1.x,p1.z,p2.x,p2.z,o.x,o.z);
			return true;
		}
	}
	else
		return false;

}

bool outCollisionToSquare(float x, float z, point &p1, point &p3)
{
	point o(x, z);
	point d1(p1.x, p1.z), d2(p1.x, p3.z), d3(p3.x, p3.z), d4(p3.x, p1.z);
	if (JoinCircleLine(o, RadiusOfPerson, d1, d2) || JoinCircleLine(o, RadiusOfPerson, d2, d3) ||
		JoinCircleLine(o, RadiusOfPerson, d3, d4) || JoinCircleLine(o, RadiusOfPerson, d1, d4))
		return true;
	else
		return false;
}

bool outCollisionToSquare(point o, point &p1, point &p3)
{
	point d1(p1.x, p1.z), d2(p1.x, p3.z), d3(p3.x, p3.z), d4(p3.x, p1.z);
	if (JoinCircleLine(o, RadiusOfPerson, d1, d2) || JoinCircleLine(o, RadiusOfPerson, d2, d3) ||
		JoinCircleLine(o, RadiusOfPerson, d3, d4) || JoinCircleLine(o, RadiusOfPerson, d1, d4))
		return true;
	else
		return false;
}

bool outCollisionToCircle(float x, float z, point &o, float r)
{
	float distance = sqrt((x - o.x)*(x - o.x) + (z - o.z)*(z - o.z));
	if (distance < r + RadiusOfPerson)
		return true;
	else
		return false;
}
bool inCollisionToSquare(float *eye, float *center, point &p1, point &p2, point &p3, point &p4)
{
	return false;
}

void move(const float *eye, const float *center, float *eye_next, float *center_next, direction dir)
{
	const float distance = StepLength;
	float x_eye = eye[0], x_cen = center[0];
	float z_eye = eye[2], z_cen = center[2];
	float len = sqrt((x_cen - x_eye)*(x_cen - x_eye) + (z_cen - z_eye)*(z_cen - z_eye));

	if (x_cen - x_eye<ZERO&&x_cen - x_eye>-ZERO)
		x_cen = x_eye;
	if (z_cen - z_eye<ZERO&&z_cen - z_eye>-ZERO)
		z_cen = z_eye;

	switch (dir) {
	case front:eye_next[0] = distance*(x_cen - x_eye) / len + x_eye;
		eye_next[2] = distance*(z_cen - z_eye) / len + z_eye;
		center_next[0] = eye_next[0] + x_cen - x_eye;
		center_next[2] = eye_next[2] + z_cen - z_eye;
		break;
	case back:
		eye_next[0] = distance*(x_eye - x_cen) / len + x_eye;
		eye_next[2] = distance*(z_eye - z_cen) / len + z_eye;
		center_next[0] = eye_next[0] + x_cen - x_eye;
		center_next[2] = eye_next[2] + z_cen - z_eye;
		break;
	case left_ward:
		eye_next[0] = distance*(z_cen - z_eye) / len + x_eye;
		eye_next[2] = distance*(x_eye - x_cen) / len + z_eye;
		center_next[0] = eye_next[0] + x_cen - x_eye;
		center_next[2] = eye_next[2] + z_cen - z_eye;
		break;
	case right_ward:
		eye_next[0] = distance*(z_eye - z_cen) / len + x_eye;
		eye_next[2] = distance*(x_cen - x_eye) / len + z_eye;
		center_next[0] = eye_next[0] + x_cen - x_eye;
		center_next[2] = eye_next[2] + z_cen - z_eye;

		break;
	default:break;
	}
	return;
}

void rotate(const float *eye, const float *center, float *eye_next, float *center_next, direction dir)
{
	const float angle = 1.0f / (10 * PI);
	float x_eye, x_cen, z_eye, z_cen;
	x_eye = eye[0], z_eye = eye[2], x_cen = center[0], z_cen = center[2];
	switch (dir) {
	case left_ward: {
		center_next[0] = x_eye + (x_cen - x_eye)*cos(angle) + (z_cen - z_eye)*sin(angle);
		center_next[2] = z_eye + (z_cen - z_eye)*cos(angle) - (x_cen - x_eye)*sin(angle);
		break;
	}
	case right_ward: {
		center_next[0] = x_eye + (x_cen - x_eye)*cos(angle) - (z_cen - z_eye)*sin(angle);
		center_next[2] = z_eye + (z_cen - z_eye)*cos(angle) + (x_cen - x_eye)*sin(angle);
		break;
	}
	default:break;
	}
}

int myRoonNo(float x, float z)
{
	if (x >= -49 && x <= -20.5) { //room 1, 2, 3
		if (z >= -44.5 && z <= -15.5) {
			return 1;
		}
		else if (z >= -14.5&&z <= 14.5) {
			return 2;
		}
		else if (z >= 15.5&&z <= 44.5) {
			return 3;
		}
	}
	else if (x >= -19.5&&x <= 9.5) {//room4, 5, 6, door 3
		if (x <= -0.5 &&z >= -64.5&&z <= -44.5) {
			return 4;
		}
		else if (z >= -44.5 && z <= 14.5) {
			return 5;
		}
		else if (z >= 15.5&&z <= 44.5) {
			return 6;
		}
		else if (z >= 14.5&&z <= 15.5&&x <= 0 && x >= -10) {
			return 10;
		}
	}
	else if (x >= 9.5 && x <= 49) {//room7
		if (z >= -44.5 && z <= 44.5) {
			return 7;
		}
	}
	else if (x >= -20.5 && x <= -19.5) {//door 1, 2, wall
		if (z >= -5 && z <= -5) {
			return 9;
		}
		else if (z >= -35 && z <= -25) {
			return 8;
		}
	}
	else { //out of the house
		
	}
	return 0;
}



bool CollosionTest(float x, float z, bool door1_open, bool door2_open, bool door3_open, bool wall_open)
{
	int roomNo = myRoonNo(x, z);
	point o(x, z);
	switch (roomNo) {
	case 1: {
		printf("in111111111111111111111\n");
		point p1(-50, -45);
		point p2(-49, -15);
		point p3(-20, -44);
		point p4(-19.5, -14.5);
		point p5(-20.5, -45);
		point p6(-50, -15.5);
		point p7(-20.5, -25);
		point p8(-19.5, -35);
		if (door1_open) {
			bool bump1 = outCollisionToSquare(o, p1, p2);
			bool bump2 = outCollisionToSquare(o, p1, p3);
			bool bump3 = outCollisionToSquare(o, p4, p6);
			bool bump4 = outCollisionToSquare(o, p4, p7);
			bool bump5 = outCollisionToSquare(o, p5, p8);
			return bump1 | bump2 | bump3 | bump4 | bump5;
		}
		else {
			bool bump1 = outCollisionToSquare(o, p1, p2);
			bool bump2 = outCollisionToSquare(o, p1, p3);
			bool bump3 = outCollisionToSquare(o, p4, p6);
			bool bump4 = outCollisionToSquare(o, p4, p5);
			return bump1 | bump2 | bump3 | bump4;
		}
		break;
	}
	case 2: {
		printf("in111111111111111111111\n");
		point p1(-50, -15.5);
		point p2(-19.5, -14.5);
		point p3(-49, 15.5);
		point p4(-19.5, 15.5);
		point p5(-20.5, -15.5);
		point p6(-50, 14.5);
		point p7(-20.5, 5);
		point p8(-19.5, -5);
		if (door2_open) {
			bool bump1 = outCollisionToSquare(o, p1, p2);
			bool bump2 = outCollisionToSquare(o, p1, p3);
			bool bump3 = outCollisionToSquare(o, p4, p6);
			bool bump4 = outCollisionToSquare(o, p4, p7);
			bool bump5 = outCollisionToSquare(o, p5, p8);
			return bump1 | bump2 | bump3 | bump4 | bump5;
		}
		else {
			bool bump1 = outCollisionToSquare(o, p1, p2);
			bool bump2 = outCollisionToSquare(o, p1, p3);
			bool bump3 = outCollisionToSquare(o, p4, p6);
			bool bump4 = outCollisionToSquare(o, p4, p5);
			return bump1 | bump2 | bump3 | bump4;
		}
		break;
	}
	case 3: {
		point p1(-50, 14.5);
		point p2(-19.5, 15.5);
		point p3(-49, 45);
		point p4(-19.5, 45);
		point p5(-20.5, 14.5);
		point p6(-50, 44);
		if (wall_open) {
			bool bump1 = outCollisionToSquare(o, p1, p2);
			bool bump2 = outCollisionToSquare(o, p1, p3);
			bool bump3 = outCollisionToSquare(o, p4, p6);
			return bump1 | bump2 | bump3;
		}
		else {
			bool bump1 = outCollisionToSquare(o, p1, p2);
			bool bump2 = outCollisionToSquare(o, p1, p3);
			bool bump3 = outCollisionToSquare(o, p4, p6);
			bool bump4 = outCollisionToSquare(o, p4, p5);
			return bump1 | bump2 | bump3 | bump4;
		}
		break;
	}
	case 4: {
		point p1(-20, -44.5);
		point p2(-19.5, -64.5);
		point p3(0.5, -65);
		point p4(-0.5, -44);
			bool bump1 = outCollisionToSquare(o, p1, p2);
			bool bump2 = outCollisionToSquare(o, p2, p3);
			bool bump3 = outCollisionToSquare(o, p3, p4);
			return bump1 | bump2 | bump3;
		break;
	}
	case 5: {
		point p1(-19.5, -14.5);
		point p2(-20.5, -25);
		point p3(-19.5, -35);
		point p4(-20.5, -45);
		
		point p5(-19.5, 15.5);
		point p6(-20.5, 5);
		point p7(-19.5, -5);
		point p8(-20.5, -15.5);

		point p9(10.5, 14.5);
		point p10(0, 15.5);
		point p11(-10, 14.5);
		point p12(-20.5, 15.5);

		point p13(-0.5, -44);
		point p14(50, -45);

		bool bump1, bump2, bump3, bump4;
		if (door1_open) {
			bump1 = outCollisionToSquare(o, p1, p2) | outCollisionToSquare(o, p3, p4);
		}
		else {
			bump1 = outCollisionToSquare(o, p1, p4);
		}
		if (door2_open) {
			bump2 = outCollisionToSquare(o, p5, p6) | outCollisionToSquare(o, p7, p8);
		}
		else {
			bump2 = outCollisionToSquare(o, p5, p8);
		}
		if (door3_open) {
			bump3 = outCollisionToSquare(o, p9, p10) | outCollisionToSquare(o, p11, p12);
		}
		else {
			bump3 = outCollisionToSquare(o, p9, p12);
		}
		bump4 = outCollisionToSquare(o, p13, p14);
		return bump1 | bump2 | bump3 | bump4;

		break;
	}
	case 6: {
		point p1(-20.5, 45);
		point p2(-19.5, 14.5);
		point p3(10.5, 44);
		point p4(10.5, 14.5);
		point p5(9.5, 45);
		point p6(0, 15.5);
		point p7(-10, 14.5);
		point p8(-20.5, 15.5);

		bool bump1 = outCollisionToSquare(o, p1, p2);
		bool bump2 = false, bump4 = false;
		if (wall_open) {
			bump2 = outCollisionToSquare(o, p1, p3);
		}
		bool bump3 = outCollisionToSquare(o, p4, p5);
		if (door3_open)
		{
			bump4 = outCollisionToSquare(o, p4, p6) | outCollisionToSquare(o, p7, p8);
		}
		else {
			bump4 = outCollisionToSquare(o, p4, p8);
		}
			return bump1 | bump2 | bump3 | bump4;
		break;
	}
	case 7: {
		point p1(-0.5, -44);
		point p2(50, -45);
		point p3(49, 45);
		point p4(9.5, 44);
		point p5(10.5, 14.5);
		bool bump1 = outCollisionToSquare(o, p1, p2);
		bool bump2 = outCollisionToSquare(o, p2, p3);
		bool bump3 = outCollisionToSquare(o, p3, p4);
		bool bump4 = outCollisionToSquare(o, p4, p5);
		return bump1 | bump2 | bump3 | bump4;

		break;
	}
	case 8: {
		point p1(-19.5, -14.5);
		point p2(-20.5, -25);
		point p3(-19.5, -35);
		point p4(-20.5, -45);
		bool bump1 = outCollisionToSquare(o, p1, p2);
		bool bump2 = outCollisionToSquare(o, p3, p4);
		return bump1 | bump2;
		break;
	}
	case 9: {
		point p1(-19.5, 15.5);
		point p2(-20.5, 5);
		point p3(-19.5, -5);
		point p4(-20.5, -15.5);
		bool bump1 = outCollisionToSquare(o, p1, p2);
		bool bump2 = outCollisionToSquare(o, p3, p4);
		return bump1 | bump2;
		break;
	}
	case 10: {
		point p1(10.5, 14.5);
		point p2(0, 15.5);
		point p3(-10, 14.5);
		point p4(-20.5, 15.5);
		bool bump1 = outCollisionToSquare(o, p1, p2);
		bool bump2 = outCollisionToSquare(o, p3, p4);
		return bump1 | bump2;

		break;
	}
	default: {
		return false;
		break;
	}
	}
	
}
//bool Person::outCollisionToSquare(float *eye, float *center, point &p1,point &p3) 
//{
//	point o(eye[0], eye[2]);
//	point d1(p1.x, p1.z), d2(p1.x, p3.z), d3(p3.x, p3.z), d4(p3.x, p1.z);
//	if (JoinCircleLine(o, RadiusOfPerson, d1, d2) || JoinCircleLine(o, RadiusOfPerson, d2, d3) ||
//		JoinCircleLine(o, RadiusOfPerson, d3, d4) || JoinCircleLine(o, RadiusOfPerson, d1, d4))
//		return true;
//	else
//		return false;
//}
//
//bool Person::outCollisionToCircle(float *eye, float *center, point &o, float r)
//{
//	float distance = sqrt((eye[0] - o.x)*(eye[0] - o.x) + (eye[2] - o.z)*(eye[2] - o.z));
//	if (distance < r + RadiusOfPerson)
//		return true;
//	else
//		return false;
//}
//bool Person::inCollisionToSquare(float *eye, float *center, point &p1, point &p2, point &p3, point &p4)
//{
//	return false;
//}
//
//void Person::move(const float *eye, const float *center, float *eye_next, float *center_next, direction dir)
//{
//	const float distance = 1.0f;
//	float x_eye = eye[0], x_cen = center[0];
//	float z_eye = eye[2], z_cen = center[2];
//	float len = sqrt((x_cen - x_eye)*(x_cen - x_eye) + (z_cen - z_eye)*(z_cen - z_eye));
//
//	if (x_cen - x_eye<ZERO&&x_cen - x_eye>-ZERO)
//		x_cen = x_eye;
//	if (z_cen - z_eye<ZERO&&z_cen - z_eye>-ZERO)
//		z_cen = z_eye;
//
//	switch (dir) {
//	case front:eye_next[0] = distance*(x_cen - x_eye) / len + x_eye;
//		eye_next[2] = distance*(z_cen - z_eye) / len + z_eye;
//		center_next[0] = eye[0] + x_cen - x_eye;
//		center_next[2] = eye[2] + z_cen - z_eye;
//		break;
//	case back:
//		eye_next[0] = distance*(x_eye - x_cen) / len + x_eye;
//		eye_next[2] = distance*(z_eye - z_cen) / len + z_eye;
//		center_next[0] = eye[0] + x_cen - x_eye;
//		center_next[2] = eye[2] + z_cen - z_eye;
//		break;
//	case left_ward:
//		eye_next[0] = distance*(z_cen - z_eye) / len + x_eye;
//		eye_next[2] = distance*(x_eye - x_cen) / len + z_eye;
//		center_next[0] = eye[0] + x_cen - x_eye;
//		center_next[2] = eye[2] + z_cen - z_eye;
//		break;
//	case right_ward: 
//		eye_next[0] = distance*(z_eye - z_cen) / len + x_eye;
//		eye_next[2] = distance*(x_cen - x_eye) / len + z_eye;
//		center_next[0] = eye[0] + x_cen - x_eye;
//		center_next[2] = eye[2] + z_cen - z_eye;
//
//		break;
//	default:break;
//	}
//	return;
//}
//
//void Person::rotate(const float *eye, const float *center, float *eye_next, float *center_next, direction dir)
//{
//	const float angle = 1.0f / (10 * PI);
//	float x_eye, x_cen, z_eye, z_cen;
//	x_eye = eye[0], z_eye = eye[2], x_cen = center[0], z_cen = center[2];
//	switch (dir) {
//	case left_ward: {
//		center_next[0] = x_eye + (x_cen - x_eye)*cos(angle) + (z_cen - z_eye)*sin(angle);
//		center_next[2] = z_eye + (z_cen - z_eye)*cos(angle) - (x_cen - x_eye)*sin(angle);
//		break;
//	}
//	case right_ward: {
//		center_next[0] = x_eye + (x_cen - x_eye)*cos(angle) - (z_cen - z_eye)*sin(angle);
//		center_next[2] = z_eye + (z_cen - z_eye)*cos(angle) + (x_cen - x_eye)*sin(angle);
//		break;
//	}
//	default:break;
//	}
//}