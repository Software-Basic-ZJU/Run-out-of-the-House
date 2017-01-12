#ifndef _UTIL_H_
#define _UTIL_H_

//#include <GL/GLUT.h>
//#include <cstdio>
//#include <cstring>
//#include <cstdlib>
#include <windows.h>
#include <stdlib.h>
#include "GL/glut.h"
#include <stdio.h>
#include <string.h>

using namespace std;

#pragma pack(2)

typedef unsigned short WORD;
//typedef unsigned  int DWORD;
typedef long LONG;

//typedef struct tagBITMAPFILEHEADER
//{
//    WORD bfType; //说明文件类型，BMP图片时该值为4D42H
//    DWORD bfSize; //说明该位图大小，单位字节
//    WORD bfReserved1; //设为0
//    WORD bfReserved2; //设为0
//    DWORD bfOffBits; //图片信息偏移位置
//} BITMAPFILEHEADER;

//typedef struct BITMAPINFOHEADER
//{
//    DWORD biSize; //说明该结构实例需要的字节数
//    DWORD biWidth; //图片宽，单位像素
//    DWORD biHeight; //图片高， 单位像素
//    WORD biPlanes; //表示平面属，等于1
//    WORD biBitCount; //表示每个像素所需字节（1、4、8、16、24、32)
//    DWORD biCompression; //表示压缩类型（BI_RGB(0), BI_RLE8, BI_RLE4, BI_BITFIELDS, BI_JEPG)
//    DWORD biSizeImage; //图像大小， 字节为单位
//    DWORD biXPelsPerMeter; //水平分辨率，单位px/m
//    DWORD biYPelsPerMeter; //垂直分辨率，单位px/m
//    DWORD biClrUsed; //使用的颜色索引数，0则全用
//    DWORD biClrlmportant; //重要颜色索引数，0则全是
//} BITMAPINFOHEADER;

#define NUM 4

extern GLuint texture[NUM];

bool WriteBitmapFile(char * filename,int width,int height,unsigned char * bitmapData);
void SaveScreenShot();


#endif
