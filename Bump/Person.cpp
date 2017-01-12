#include<stdio.h>  
#include <math.h>
#include "Person.h"
#define PLUSS +5
#define MINUSS +0.5
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
float cosOfPoints(point o, point a, point b)
{
	return ((a.x - o.x)*(b.x - o.x) + (a.z - o.z)*(b.z - o.z)) / (distanceBetweenPoints(a, o)*distanceBetweenPoints(b, o));
}

//默认方向向量模长为1，以后可能要改
float cosOfPoints(point o, point a, localVector p)
{
	return ((a.x - o.x)*(p.x) + (a.z - o.z)*(p.z)) / (distanceBetweenPoints(a, o));
}

int nearDoor(point eyePos, point centerPos)
{
	int roomNo = myRoonNo(eyePos.x, eyePos.z);
	float minDoorRadius = 15.0;
	float maxcos = 0.6f;
	point wall_center(-20.5, 20.0);
	point door1_center(-20.5, -30.0);
	point door2_center(-20.5, 0.0);
	point door3_center(-5.0, 15.5);
	point key_Center(-40, 35);
	localVector door124_out_n(1, 0);
	localVector door3_out_n(0, -1);

	printf("test\n");
	
	if (distanceBetweenPoints(eyePos, door1_center) <= minDoorRadius)
	{
		float ang = cosOfPoints(eyePos, centerPos, door124_out_n);
		printf("door11:%f\n", ang);
		if((roomNo == 5 && ang < -maxcos) || (roomNo == 1 && ang > maxcos))
		{
			printf("door111\n");
			return 1;
		}
	}
	if (distanceBetweenPoints(eyePos, door2_center) <= minDoorRadius)
	{
		float ang = cosOfPoints(eyePos, centerPos, door124_out_n);
		printf("door22:%f\n", ang);
		if ((roomNo == 5 && ang < -maxcos) || (roomNo == 2 && ang > maxcos))
		{
			printf("door222\n");
			return 2;
		}
	}
	if (distanceBetweenPoints(eyePos, door3_center) <= minDoorRadius)
	{
		
		float ang = cosOfPoints(eyePos, centerPos, door3_out_n);
		printf("door33:%f\n", ang);
		if ((roomNo == 5 && ang < -maxcos) || (roomNo == 6 && ang > maxcos))
		{
			return 3;
		}
	}
	if (distanceBetweenPoints(eyePos, wall_center) <= minDoorRadius)
	{
		float ang = cosOfPoints(eyePos, centerPos, door124_out_n);
		printf("door44:%f\n", ang);
		if ((roomNo == 6 && ang < -maxcos) || (roomNo == 3 && ang > maxcos))
		{
			return 4;
		}
	}
	if (distanceBetweenPoints(eyePos, key_Center) <= minDoorRadius)
	{
		float ang = cosOfPoints(eyePos, centerPos, key_Center);
		printf("key11:%f\n", ang);
		if (ang>maxcos)
		{
			printf("door111\n");
			return 5;
		}
	}
	return 0;
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
bool outCollisionToCircle(point &myEye, point &o, float r)
{
	return outCollisionToCircle(myEye.x, myEye.z, o, r);
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
	const float wallNS_1_lb = -50.0, wallNS_1_rb = -49.0, wallNS_2_lb = -20.5, wallNS_2_rb = -19.5, wallNS_3_lb = -0.5, wallNS_3_rb = 0.5, wallNS_4_lb = 9.5, wallNS_4_rb = 10.5, wallNS_5_lb = 49, wallNS_5_rb = 50;
	const float wallEW_1_db = -65.0 PLUSS, wallEW_1_ub = -64.0 PLUSS, wallEW_2_db = -45.0 PLUSS, wallEW_2_ub = -44.0 PLUSS, wallEW_3_db = -15.5 PLUSS, wallEW_3_ub = -14.5 PLUSS, wallEW_4_db = 14.5 PLUSS, wallEW_4_ub = 15.5 PLUSS, wallEW_5_db = 44 PLUSS, wallEW_5_ub = 45 PLUSS;
	const float door1open_db = -31.0 PLUSS, door1open_ub = -30.0 PLUSS, door1open_lb = -30.0, door1open_rb = -20.0, door1close_ub = -25.0 PLUSS, door1close_db = -35.0 PLUSS;
	const float door2open_db = 4.0 PLUSS, door2open_ub = 5.0 PLUSS, door2open_lb = -30.0, door2open_rb = -20.0, door2close_ub = 5.0 PLUSS, door2close_db = -5.0 PLUSS;
	const float door3open_db = 15.0 PLUSS, door3open_ub = 25.0 PLUSS, door3open_lb = -1.0 MINUSS, door3open_rb = 0 MINUSS, door3close_lb = -10.0, door3close_rb = 0.0;
	if (z < wallEW_1_db) {
		return 20;
	}
	if (x >= wallNS_1_rb && x <= wallNS_2_lb) { //room 1, 2, 3
		if (z >= wallEW_2_ub && z <= wallEW_3_db) {
			return 1;
		}
		else if (z >= wallEW_3_ub&&z <= wallEW_4_db){
			return 2;
		}
		else if (z >= wallEW_4_ub&&z <= wallEW_5_db) {
			return 3;
		}
	}
	else if (x >= wallNS_2_rb&&x <= 9.5) {//room4, 5, 6, door 3
		if (x <= wallNS_3_lb &&z >= wallEW_1_ub&&z <= wallEW_2_ub) {
			return 4;
		}
		else if (z >= wallEW_2_ub && z <= wallEW_4_db) {
			return 5;
		}
		else if (z >= wallEW_4_ub&&z <= wallEW_5_db) {
			return 6;
		}
		else if (z >= wallEW_4_db&&z <= wallEW_4_ub&&x <= 0 && x >= door3close_lb && x <= door3close_rb) {
			return 10;
		}
	}
	else if (x >= wallNS_4_lb && x <= wallNS_5_lb) {//room7
		if (z >= wallEW_2_db && z <= wallEW_5_ub) {
			return 7;
		}
	}
	else if (x >= wallNS_2_lb && x <= wallNS_2_rb) {//door 1, 2, wall
		if (z >= door1close_db && z <= door1close_ub) {
			return 9;
		}
		else if (z >= door2close_db && z <= door2close_ub) {
			return 8;
		}
	}
	else { //out of the house
		
	}
	return 0;
}



bool CollosionTest(float x, float z, bool door1_open, bool door2_open, bool door3_open, bool wall_open, bool has_Key)
{
	int roomNo = myRoonNo(x, z);
	const float wallNS_1_lb = -50.0, wallNS_1_rb = -49.0, wallNS_2_lb = -20.5, wallNS_2_rb = -19.5, wallNS_3_lb = -0.5, wallNS_3_rb = 0.5, wallNS_4_lb = 9.5, wallNS_4_rb = 10.5, wallNS_5_lb = 49, wallNS_5_rb = 50;
	const float wallEW_1_db = -65.0 PLUSS, wallEW_1_ub = -64.0 PLUSS, wallEW_2_db = -45.0 PLUSS, wallEW_2_ub = -44.0 PLUSS, wallEW_3_db = -15.5 PLUSS, wallEW_3_ub = -14.5 PLUSS, wallEW_4_db = 14.5 PLUSS, wallEW_4_ub = 15.5 PLUSS, wallEW_5_db = 44 PLUSS, wallEW_5_ub = 45 PLUSS;
	const float door1open_db = -31.0 PLUSS PLUSS, door1open_ub = -30.0 PLUSS PLUSS, door1open_lb = -30.0, door1open_rb = -20.0, door1close_ub = -25.0 PLUSS, door1close_db = -35.0 PLUSS;
	const float door2open_db = 4.0 PLUSS, door2open_ub = 5.0 PLUSS, door2open_lb = -30.0, door2open_rb = -20.0, door2close_ub = 5.0 PLUSS, door2close_db = -5.0 PLUSS;
	const float door3open_db = 15.0 PLUSS, door3open_ub = 25.0 PLUSS, door3open_lb = -1.0 MINUSS, door3open_rb = 0 MINUSS, door3close_lb = -10.0, door3close_rb = 0.0;
	const float exit_door_lb = -15.0, exit_door_rb = -5.0;
//	const float door1open_db = 0, door1open_up = 0, door1open_lb = 0, door1open_rb = 0, door1close_ub = 0, door1close_db = 0;

	point o(x, z);
	switch (roomNo) {
	case 1: {
		printf("in111111111111111111111\n");
		
		point p1(wallNS_1_lb, wallEW_2_db);
		point p2(wallNS_2_rb, wallEW_2_ub);
		point p3(wallNS_1_rb, wallEW_3_ub);
		point p4(wallNS_2_rb, wallEW_3_ub);
		point p5(wallNS_2_lb, wallEW_2_db);
		point p6(wallNS_1_lb, wallEW_3_db);
		point p7(wallNS_2_lb, door1close_ub);
		point p8(wallNS_2_rb, door1close_db);
		point p9(door1open_lb, door1open_db);
		point p10(door1open_rb, door1open_ub);
		point p11(-49.0, -36.0);
		point p12(-35, -16);
		if (door1_open) {
			bool bump1 = outCollisionToSquare(o, p1, p2);
			bool bump2 = outCollisionToSquare(o, p1, p3);
			bool bump3 = outCollisionToSquare(o, p4, p6);
			bool bump4 = outCollisionToSquare(o, p4, p7);
			bool bump5 = outCollisionToSquare(o, p5, p8);
			bool bump6 = outCollisionToSquare(o, p9, p10);
			bool bump7 = outCollisionToSquare(o, p11, p12);
			if (bump1)
				printf("bump1\n");
			if (bump2)
				printf("bump2\n");
			if (bump3)
				printf("bump3\n");
			if (bump4)
				printf("bump4\n");
			if (bump5)
				printf("bump5\n");
			if (bump6)
				printf("bumpdoor\n");
			return bump1 | bump2 | bump3 | bump4 | bump5 | bump6 | bump7;
		}
		else {
			bool bump1 = outCollisionToSquare(o, p1, p2);
			bool bump2 = outCollisionToSquare(o, p1, p3);
			bool bump3 = outCollisionToSquare(o, p4, p6);
			bool bump4 = outCollisionToSquare(o, p4, p5);
			bool bump7 = outCollisionToSquare(o, p11, p12);
			if (bump1)
				printf("bump1\n");
			if (bump2)
				printf("bump2\n");
			if (bump3)
				printf("bump3\n");
			if (bump4)
				printf("bump4\n");
			return bump1 | bump2 | bump3 | bump4 | bump7;
		}
		break;
	}
	case 2: {
		printf("in2222222222222222222222222\n");
		point p1(wallNS_1_lb, wallEW_3_db);
		point p2(wallNS_2_rb, wallEW_3_ub);
		point p3(wallNS_1_rb, wallEW_4_ub);
		point p4(wallNS_2_rb, wallEW_4_ub);
		point p5(wallNS_2_lb, wallEW_3_db);
		point p6(wallNS_1_lb, wallEW_4_db);
		point p7(wallNS_2_lb, door2close_ub);
		point p8(wallNS_2_rb, door2close_db);
		point p9(door2open_lb, door2open_db);
		point p10(door2open_rb, door2open_ub);
		point p11(-49.0, 3.5);
		point p12(-35, 15);
		if (door2_open) {
			bool bump1 = outCollisionToSquare(o, p1, p2);
			bool bump2 = outCollisionToSquare(o, p1, p3);
			bool bump3 = outCollisionToSquare(o, p4, p6);
			bool bump4 = outCollisionToSquare(o, p4, p7);
			bool bump5 = outCollisionToSquare(o, p5, p8);
			bool bump6 = outCollisionToSquare(o, p9, p10);
			bool bump7 = outCollisionToSquare(o, p11, p12);
			if (bump1)
				printf("bump1\n");
			if (bump2)
				printf("bump2\n");
			if (bump3)
				printf("bump3\n");
			if (bump4)
				printf("bump4\n");
			if (bump5)
				printf("bump5\n");
			if(bump6)
				printf("bumpdoor\n");
			return bump1 | bump2 | bump3 | bump4 | bump5 | bump6 | bump7;
		}
		else {
			bool bump1 = outCollisionToSquare(o, p1, p2);
			bool bump2 = outCollisionToSquare(o, p1, p3);
			bool bump3 = outCollisionToSquare(o, p4, p6);
			bool bump4 = outCollisionToSquare(o, p4, p5);
			bool bump7 = outCollisionToSquare(o, p11, p12);
			return bump1 | bump2 | bump3 | bump4 | bump7;
		}
		break;
	}
	case 3: {
		printf("in333333333333333333333\n");
		point p1(wallNS_1_lb, wallEW_4_db);
		point p2(wallNS_2_rb, wallEW_4_ub);
		point p3(wallNS_1_rb, wallEW_5_ub);
		point p4(wallNS_2_rb, wallEW_5_ub);
		point p5(wallNS_2_lb, wallEW_4_db);
		point p6(wallNS_1_lb, wallEW_5_db);
		point p7(-49, 46);
		point p8(-37, 21);
		if (wall_open) {
			bool bump1 = outCollisionToSquare(o, p1, p2);
			bool bump2 = outCollisionToSquare(o, p1, p3);
			bool bump3 = outCollisionToSquare(o, p4, p6);
			bool bump5 = outCollisionToSquare(o, p7, p8);
			if (bump1)
				printf("bump1\n");
			if (bump2)
				printf("bump2\n");
			return bump1 | bump2 | bump3 | bump5;
		}
		else {
			bool bump1 = outCollisionToSquare(o, p1, p2);
			bool bump2 = outCollisionToSquare(o, p1, p3);
			bool bump3 = outCollisionToSquare(o, p4, p6);
			bool bump4 = outCollisionToSquare(o, p4, p5);
			bool bump5 = outCollisionToSquare(o, p7, p8);
			if (bump1)
				printf("bump1\n");
			if (bump2)
				printf("bump2\n");
			if (bump3)
				printf("bump3\n");
			if (bump4)
				printf("bump4\n");
			return bump1 | bump2 | bump3 | bump4 | bump5;
		}


		break;
	}
	case 4: {
		printf("in4444444444444444444444\n");
		point p1(wallNS_2_lb, wallEW_1_db);
		point p2(wallNS_3_rb, wallEW_1_ub);
		point p3(wallNS_2_rb, wallEW_2_ub);
		point p4(wallNS_3_rb, wallEW_2_ub);
		point p5(wallNS_3_lb, wallEW_1_db);
		point p6(wallNS_2_lb, wallEW_2_db);
		point p7(exit_door_lb, wallEW_1_ub);
		point p8(exit_door_rb, wallEW_1_db);
		bool bump2 = outCollisionToSquare(o, p1, p3);
		bool bump3 = outCollisionToSquare(o, p4, p5);
		bool bump1;
		if (has_Key) {
			bump1 = outCollisionToSquare(o, p1, p7) | outCollisionToSquare(o, p8, p2);
		}
		else
			bump1 = outCollisionToSquare(o, p1, p2);
			

			if (bump1)
				printf("bump1\n");
			if (bump2)
				printf("bump2\n");
			if (bump3)
				printf("bump3\n");
			return bump1 | bump2 | bump3;
		break;
	}
	case 5: {
		printf("in5555555555555555555555555\n");

		point p1(wallNS_2_lb, wallEW_2_db);
		point p2(wallNS_2_rb, door1close_db);
		point p3(wallNS_2_lb, door1close_ub);
		point p4(wallNS_2_rb, wallEW_3_ub);
		
		point p5(wallNS_2_lb, wallEW_3_db);
		point p6(wallNS_2_rb, door2close_db);
		point p7(wallNS_2_lb, door2close_ub);
		point p8(wallNS_2_rb, wallEW_4_ub);

		point p9(wallNS_2_lb, wallEW_4_db);
		point p10(door3close_lb, wallEW_4_ub);
		point p11(door3close_rb, wallEW_4_db);
		point p12(wallNS_4_rb, wallEW_4_ub);

		point p13(wallNS_3_lb, wallEW_2_db);
		point p14(wallNS_4_rb, wallEW_2_ub);

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
		if (bump1)
			printf("bump1\n");
		if (bump2)
			printf("bump2\n");
		if (bump3)
			printf("bump3\n");
		if (bump4)
			printf("bump4\n");
		return bump1 | bump2 | bump3 | bump4;

		break;
	}
	case 6: {
		printf("in666666666666666666666666666\n");
		point p1(wallNS_2_lb, wallEW_4_db);
		point p2(wallNS_4_rb, wallEW_4_ub);
		point p3(wallNS_2_rb, wallEW_5_ub);
		point p4(wallNS_4_rb, wallEW_5_ub);
		point p5(wallNS_4_lb, wallEW_4_db);
		point p6(wallNS_2_lb, wallEW_5_db);
		point p7(door3close_lb, wallEW_4_ub);
		point p8(door3close_rb, wallEW_4_db);
		point p9(door3open_lb, door3open_db);
		point p10(door3open_rb, door3open_ub);

		point p11(-4, 34);
		point p12(4, 42);
		bool bump1, bump4, bump5;
		if (door3_open)
		{
			bump1 = outCollisionToSquare(o, p1, p7) || outCollisionToSquare(o, p8, p2);
			bump5 = outCollisionToSquare(o, p9, p10);
		}
		else {
			bump1 = outCollisionToSquare(o, p1, p2);
			bump5 = false;
		}
		bool bump2 = outCollisionToSquare(o, p4, p5);
		bool bump3 = outCollisionToSquare(o, p4, p6);
		bool bump6 = outCollisionToSquare(o, p11, p12);
		if (wall_open) {
			bump4 = false;
		}
		else {
			bump4 = outCollisionToSquare(o, p1, p3);
		}
		if (bump1)
			printf("bump1\n");
		if (bump2)
			printf("bump2\n");
		if (bump3)
			printf("bump3\n");
		if (bump4)
			printf("bump4\n");
		if (bump5)
			printf("bump5\n");
		return bump1 | bump2 | bump3 | bump4 | bump5 | bump6;
	}
	case 7: {
		printf("in777777777777777777777\n");
		point p1(wallNS_4_lb, wallEW_5_ub);
		point p2(wallNS_4_rb, wallEW_4_db);
		point p3(wallNS_5_rb, wallEW_5_db);
		point p4(wallNS_5_rb, wallEW_2_ub);
		point p5(wallNS_4_lb, wallEW_2_db);
		point p6(wallNS_5_lb, wallEW_5_ub);
		point p7(17, 16.5);
		point p8(23, 21.5);
		point p9(37, -10);
		point p10(43, -5);
		point oOfTable(30,20);
		point oOfChair(30,6);
		float rOfTable = 6, rOfChair = 2;

		bool bump1 = outCollisionToSquare(o, p1, p2);
		bool bump2 = outCollisionToSquare(o, p1, p3);
		bool bump3 = outCollisionToSquare(o, p4, p5);
		bool bump4 = outCollisionToSquare(o, p4, p6);
		bool bump5 = outCollisionToSquare(o, p7, p8);
		bool bump6 = outCollisionToCircle(o, oOfChair, rOfChair);
		bool bump7 = outCollisionToCircle(o, oOfTable, rOfTable);
		bool bump8 = outCollisionToSquare(o, p9, p10);
		if (bump1)
			printf("bump1\n");
		if (bump2)
			printf("bump2\n");
		if (bump3)
			printf("bump3\n");
		if (bump4)
			printf("bump4\n");
		return bump1 | bump2 | bump3 | bump4 | bump5 | bump6 | bump7 | bump8;

		break;
	}
	case 8: {
		printf("in888888888888888888888888\n");
		point p1(wallNS_2_lb, door1close_db);
		point p2(wallNS_2_rb, wallEW_2_ub);
		point p3(wallNS_2_lb, door1close_ub);
		point p4(wallNS_2_rb, wallEW_3_db);
		bool bump1 = outCollisionToSquare(o, p1, p2);
		bool bump2 = outCollisionToSquare(o, p3, p4);
		if (bump1)
			printf("bump1\n");
		if (bump2)
			printf("bump2\n");
		return bump1 | bump2;
		break;
	}
	case 9: {
		printf("in99999999999999999999999\n");
		point p1(wallNS_2_lb, door2close_db);
		point p2(wallNS_2_rb, wallEW_3_ub);
		point p3(wallNS_2_lb, door2close_ub);
		point p4(wallNS_2_rb, wallEW_4_db);
		bool bump1 = outCollisionToSquare(o, p1, p2);
		bool bump2 = outCollisionToSquare(o, p3, p4);
		if (bump1)
			printf("bump1\n");
		if (bump2)
			printf("bump2\n");
		return bump1 | bump2;
		break;
	}
	case 10: {
		printf("inaaaaaaaaaaaaaaaaaaaaaaaaaaa\n");
		point p1(door3close_lb, wallEW_4_ub);
		point p2(wallNS_2_rb, wallEW_4_db);
		point p3(door3close_rb, wallEW_4_ub);
		point p4(wallNS_4_rb, wallEW_4_db);
		bool bump1 = outCollisionToSquare(o, p1, p2);
		bool bump2 = outCollisionToSquare(o, p3, p4);
		if (bump1)
			printf("bump1\n");
		if (bump2)
			printf("bump2\n");
		return bump1 | bump2;

		break;
	}
	default: {
		printf("oooooooooooooooooooooooooooooo\n");
		return false;
		break;
	}
	}
	
}