#ifndef PREFIX_H
#define PREFIX_H
#pragma once
/**Dev-c++ 5.7.1 (MinGW GCC 4.8.1 32-bit) 编译命令:
 * -static-libstdc++ -static-libgcc -lglaux -lopengl32
 * -lglaux需要在-lopengl32前面
 */
#include <windows.h>             // Header File For Windows
#define GLUT_DISABLE_ATEXIT_HACK // Dev-c++编译glut需要define GLUT_DISABLE_ATEXIT_HACK
//#include <GL/gl.h>               // Header File For The OpenGL32 Library
//#include <GL/glu.h>              // Header File For The GLu32 Library
#include <gl/glew.h>
#include <GL/glut.h>
#include <gl/glaux.h>	     // Header File For The Glaux Library
//#pragma comment (lib, "glew32.lib") 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <vector>
using namespace std;

#endif
