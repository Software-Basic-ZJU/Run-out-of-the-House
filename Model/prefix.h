#ifndef PREFIX_H
#define PREFIX_H

/**Dev-c++ 5.7.1 (MinGW GCC 4.8.1 32-bit) ��������:
 * -static-libstdc++ -static-libgcc -lglaux -lopengl32
 * -lglaux��Ҫ��-lopengl32ǰ��
 */
#include <windows.h>             // Header File For Windows
#define GLUT_DISABLE_ATEXIT_HACK // Dev-c++����glut��Ҫdefine GLUT_DISABLE_ATEXIT_HACK
#include <gl/glew.h>
#include <GL/gl.h>               // Header File For The OpenGL32 Library
#include <GL/glu.h>              // Header File For The GLu32 Library
#include <GL/glut.h>
#include <GL/glaux.h>		     // Header File For The Glaux Library

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <vector>
using namespace std;

#endif
