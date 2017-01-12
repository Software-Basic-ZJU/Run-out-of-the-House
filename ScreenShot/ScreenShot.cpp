#include "ScreenShot.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define BITMAP_ID 0x4D42


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
    sprintf(Filename,"%ld.bmp",tm);
    
    WriteBitmapFile(Filename,800,600,(unsigned char*)screenData);
    //释放内存
    free(screenData);   
}
