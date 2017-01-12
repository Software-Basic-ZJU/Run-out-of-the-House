#include "ScreenShot.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define BITMAP_ID 0x4D42
#define TEXW 64
#define TEXH 64
GLuint texture[NUM];
unsigned char tex[TEXH][TEXW][3];


// 纹理标示符数组，保存两个纹理的标示符
// 描述: 通过指针，返回filename 指定的bitmap文件中数据。
// 同时也返回bitmap信息头.（不支持-bit位图）
unsigned char *LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader)
{
    FILE *filePtr;	// 文件指针
    BITMAPFILEHEADER bitmapFileHeader;	// bitmap文件头
    unsigned char	*bitmapImage;		// bitmap图像数据
    int	imageIdx = 0;		// 图像位置索引
    unsigned char	tempRGB;	// 交换变量
    
    // 以“二进制+读”模式打开文件filename
    filePtr = fopen(filename, "rb");
    if (filePtr == NULL){
        printf("%s 打开失败\n", filename);
        return NULL;
    }
    // 读入bitmap文件图
    fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);
    // 验证是否为bitmap文件
    if (bitmapFileHeader.bfType != BITMAP_ID) {
        fprintf(stderr, "Error in LoadBitmapFile: the file is not a bitmap file\n");
        return NULL;
    }
    
    // 读入bitmap信息头
    fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);
    // 将文件指针移至bitmap数据
    fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);
    // 为装载图像数据创建足够的内存
    bitmapImage = new unsigned char[bitmapInfoHeader->biSizeImage];
    // 验证内存是否创建成功
    if (!bitmapImage) {
        fprintf(stderr, "Error in LoadBitmapFile: memory error\n");
        return NULL;
    }
    
    // 读入bitmap图像数据
    fread(bitmapImage, 1, bitmapInfoHeader->biSizeImage, filePtr);
    // 确认读入成功
    if (bitmapImage == NULL) {
        fprintf(stderr, "Error in LoadBitmapFile: memory error\n");
        return NULL;
    }
    
    //由于bitmap中保存的格式是BGR，下面交换R和B的值，得到RGB格式
    for (imageIdx = 0;
         imageIdx < bitmapInfoHeader->biSizeImage; imageIdx += 3) {
        tempRGB = bitmapImage[imageIdx];
        bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
        bitmapImage[imageIdx + 2] = tempRGB;
    }
    // 关闭bitmap图像文件
    fclose(filePtr);
    return bitmapImage;
}

//WriteBitmapFile
//根据bitmapData的（RGB）数据，保存bitmap
//filename是要保存到物理硬盘的文件名（包括路径）
bool WriteBitmapFile(char * filename,int width,int height,unsigned char * bitmapData)
{
    //填充BITMAPFILEHEADER
    BITMAPFILEHEADER bitmapFileHeader;
    memset(&bitmapFileHeader,0,sizeof(BITMAPFILEHEADER));
    bitmapFileHeader.bfSize = sizeof(BITMAPFILEHEADER);
    bitmapFileHeader.bfType = 0x4d42;	//BM
    bitmapFileHeader.bfOffBits =sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    
    //填充BITMAPINFOHEADER
    BITMAPINFOHEADER bitmapInfoHeader;
    memset(&bitmapInfoHeader,0,sizeof(BITMAPINFOHEADER));
    bitmapInfoHeader.biSize = sizeof(BITMAPINFOHEADER);
    bitmapInfoHeader.biWidth = width;
    bitmapInfoHeader.biHeight = height;
    bitmapInfoHeader.biPlanes = 1;
    bitmapInfoHeader.biBitCount = 24;
    bitmapInfoHeader.biCompression = 0; //BI_RGB:不压缩
    bitmapInfoHeader.biSizeImage = width * abs(height) * 3;
    
    FILE * filePtr;			//连接要保存的bitmap文件用
    unsigned char tempRGB;	//临时色素
    int imageIdx;
    
    //交换R、B的像素位置,bitmap的文件放置的是BGR,内存的是RGB
    for (imageIdx = 0;imageIdx < bitmapInfoHeader.biSizeImage;imageIdx +=3)
    {
        tempRGB = bitmapData[imageIdx];
        bitmapData[imageIdx] = bitmapData[imageIdx + 2];
        bitmapData[imageIdx + 2] = tempRGB;
    }
    
    filePtr = fopen(filename,"wb");
    if (NULL == filePtr)
    {
        printf("screenshot file create fail\n");
        return false;
    }
    
    fwrite(&bitmapFileHeader,sizeof(BITMAPFILEHEADER),1,filePtr);
    
    fwrite(&bitmapInfoHeader,sizeof(BITMAPINFOHEADER),1,filePtr);
    
    fwrite(bitmapData,bitmapInfoHeader.biSizeImage,1,filePtr);
    
    fclose(filePtr);
    return true;
}

//保存屏幕截图
//url改一改
void SaveScreenShot()
{
    static void * screenData;
    int len = 800 * 600 * 3;
    screenData = malloc(len);
    memset(screenData,0,len);
    glReadPixels(0, 0, 800, 600, GL_RGB, GL_UNSIGNED_BYTE, screenData);
    
    //生成文件名字符串，以时间命名
    time_t tm = 0;
    tm = time(NULL);
    char Filename[256] = {0};
    sprintf(Filename,"/Users/crcrcry/XcodeProjects/OpenGL/ScreenShot/ScreenShot/images/%ld.bmp",tm);
    
    WriteBitmapFile(Filename,800,600,(unsigned char*)screenData);
    //释放内存
    free(screenData);   
}

//加载纹理的函数：
unsigned char* texload(int i, char *filename)
{
    
    BITMAPINFOHEADER bitmapInfoHeader;                                 // bitmap信息头
    unsigned char*   bitmapData;                                       // 纹理数据
    
    bitmapData = LoadBitmapFile(filename, &bitmapInfoHeader);
    glBindTexture(GL_TEXTURE_2D, texture[i]);
    // 指定当前纹理的放大/缩小过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    glTexImage2D(GL_TEXTURE_2D,
                 0, 	    //mipmap层次(通常为，表示最上层)
                 GL_RGB,	//我们希望该纹理有红、绿、蓝数据
                 bitmapInfoHeader.biWidth, //纹理宽带，必须是n，若有边框+2
                 bitmapInfoHeader.biHeight, //纹理高度，必须是n，若有边框+2
                 0, //边框(0=无边框, 1=有边框)
                 GL_RGB,	//bitmap数据的格式
                 GL_UNSIGNED_BYTE, //每个颜色数据的类型
                 bitmapData);	//bitmap数据指针
    return bitmapData;
}

//定义纹理的函数：
void init()
{

    /*是否支持多纹理*/
    const GLubyte* extensions= glGetString(GL_EXTENSIONS) ;
    bool multiTexturingSupported = strstr((const char*)extensions, "GL_ARB_multitexture");
    if(multiTexturingSupported){
        printf("Multi-Texture supported\n");
    }else{
        printf("Multi-Texture not supported\n");
    }
    
    /*多重纹理初始化
    glMultiTexCoord2fARB = (PFNGLMULTITEXCOORD2FARBPROC)wglGetProcAddress("glMultiTexCoord2fARB");
    glActiveTextureARB = (PFNGLACTIVETEXTUREARBPROC)wglGetProcAddress("glActiveTextureARB");
    glClientActiveTextureARB = (PFNGLCLIENTACTIVETEXTUREARBPROC)wglGetProcAddress("glClientActiveTextureARB");
    */
    
    glGenTextures(4, texture);                                         // 第一参数是需要生成标示符的个数, 第二参数是返回标示符的数组
    texload(0, (char *)"/Users/crcrcry/XcodeProjects/OpenGL/ScreenShot/ScreenShot/images/Monet.bmp");
    texload(1, (char *)"/Users/crcrcry/XcodeProjects/OpenGL/ScreenShot/ScreenShot/images/Crack.bmp");
    texload(3, (char *)"/Users/crcrcry/XcodeProjects/OpenGL/ScreenShot/ScreenShot/images/Spot.bmp");
    
    ProduceTexure();//下面生成自定义黑红纹理
    
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); //设置像素存储模式控制所读取的图像数据的行对齐方式.
    glTexImage2D(GL_TEXTURE_2D, 0, 3, TEXW, TEXH, 0, GL_RGB, GL_UNSIGNED_BYTE, tex);//生成2d纹理
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//放大过滤，双线性插值
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//缩小过滤，双线性插值
    
}

void glTexCubic(){
    //多重纹理设置
    int mode = 2;
    if(mode == 1){
        glActiveTexture(GL_TEXTURE0);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture[1]) ;
    }else{
        glActiveTexture(GL_TEXTURE0);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture[1]);
        //glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
        glActiveTexture(GL_TEXTURE1);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture[3]) ;
        //glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    }
    
    //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D, texture[1]) ;
    
    /*自制立方体*/
    glBegin(GL_QUADS); {
        //front
        glMultiTexCoord2f(GL_TEXTURE0, 1, 1);
        glMultiTexCoord2f(GL_TEXTURE1, 1, 1);
        glVertex3f(0.5, 0.5, 0.5);
        glMultiTexCoord2f(GL_TEXTURE0, 0, 1);
        glMultiTexCoord2f(GL_TEXTURE1, 0, 1);
        glVertex3f(-0.5, 0.5, 0.5);
        glMultiTexCoord2f(GL_TEXTURE0, 0, 0);
        glMultiTexCoord2f(GL_TEXTURE1, 0, 0);
        glVertex3f(-0.5, -0.5, 0.5);
        glMultiTexCoord2f(GL_TEXTURE0, 1, 0);
        glMultiTexCoord2f(GL_TEXTURE1, 1, 0);
        glVertex3f(0.5, -0.5, 0.5);
    }
    glEnd();
    
    
    glActiveTexture(GL_TEXTURE1);
    glDisable(GL_TEXTURE_2D);
    glActiveTexture(GL_TEXTURE0);
    
    
    glBegin(GL_QUADS); {
        //right
        glTexCoord2i(1, 1); glVertex3f(0.5, 0.5, 0.5);
        glTexCoord2i(0, 1); glVertex3f(0.5, -0.5, 0.5);
        glTexCoord2i(0, 0); glVertex3f(0.5, -0.5, -0.5);
        glTexCoord2i(1, 0); glVertex3f(0.5, 0.5, -0.5);
    }
    glEnd();
    glBegin(GL_QUADS); {
        //top
        glTexCoord2i(1, 1); glVertex3f(0.5, 0.5, 0.5);
        glTexCoord2i(0, 1); glVertex3f(0.5, 0.5, -0.5);
        glTexCoord2i(0, 0); glVertex3f(-0.5, 0.5, -0.5);
        glTexCoord2i(1, 0); glVertex3f(-0.5, 0.5, 0.5);
    }
    glEnd();
    glBegin(GL_QUADS); {
        //left
        glTexCoord2i(1, 1); glVertex3f(-0.5, -0.5, -0.5);
        glTexCoord2i(0, 1); glVertex3f(-0.5, -0.5, 0.5);
        glTexCoord2i(0, 0); glVertex3f(-0.5, 0.5, 0.5);
        glTexCoord2i(1, 0); glVertex3f(-0.5, 0.5, -0.5);
    }
    glEnd();
    glBegin(GL_QUADS); {
        //behind
        glTexCoord2i(1, 1); glVertex3f(-0.5, -0.5, -0.5);
        glTexCoord2i(0, 1); glVertex3f(-0.5, 0.5, -0.5);
        glTexCoord2i(0, 0); glVertex3f(0.5, 0.5, -0.5);
        glTexCoord2i(1, 0); glVertex3f(0.5, -0.5, -0.5);
    }
    glEnd();
    glBegin(GL_QUADS); {
        //bottom
        glTexCoord2i(1, 1); glVertex3f(-0.5, -0.5, -0.5);
        glTexCoord2i(0, 1); glVertex3f(0.5, -0.5, -0.5);
        glTexCoord2i(0, 0); glVertex3f(0.5, -0.5, 0.5);
        glTexCoord2i(1, 0); glVertex3f(-0.5, -0.5, 0.5);
    }
    glEnd();
}

void ProduceTexure(){
    /*绘制黑红纹理*/
    bool ifhr = false, ifwr = false;
    for (int h = 0; h < TEXH; h++){
        if (h % 8 == 0) ifhr = !ifhr;
        ifwr = (ifhr) ? true : false;
        for (int w = 0; w < TEXW; w++){
            //设置rgb 红黑红黑
            if (w % 8 == 0) ifwr = !ifwr;
            tex[h][w][0] = (ifwr) ? 128 : 0;
            tex[h][w][1] = 0;
            tex[h][w][2] = 0;
        }
    }
}

