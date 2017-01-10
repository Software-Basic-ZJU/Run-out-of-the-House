/**
 The bitmap's id must be surrounded by quotation marks (i.e. "Texture.bmp").

 Usage:
 GLTexture tex;
 GLTexture tex3;

 tex.Load("texture.bmp"); // Loads a bitmap
 tex.Use();				// Binds the bitmap for use

 // You can also build a texture with a single color and use it
 tex3.BuildColorTexture(255, 0, 0);	// Builds a solid red texture
 tex3.Use();				 // Binds the targa for use

 */

#include "GLTexture.h"

GLTexture::GLTexture()
{

}

GLTexture::~GLTexture()
{

}

void GLTexture::Load(char *name)
{
	// make the texture name all lower case
	texturename = _strlwr(_strdup(name));

	// strip "'s
	while (strstr(name, "\""))
		texturename = strtok(name, "\"");

	// check the file extension to see what type of texture
	if (strstr(name, ".bmp"))
		LoadBMP(name);
}

void GLTexture::mount()
{
	glEnable(GL_TEXTURE_2D);								// Enable texture mapping
	glBindTexture(GL_TEXTURE_2D, texture[0]);				// Bind the texture as the current one
	//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
}

void GLTexture::unmount(){
	glDisable(GL_TEXTURE_2D);
}

void GLTexture::LoadBMP(char *name)
{
	//printf("%s\n", name);
	// Create a place to store the texture1
	AUX_RGBImageRec *TextureImage[1];	

	// Set the pointer to NULL
	memset(TextureImage,0,sizeof(void *)*1);
	
	FILE *fp;
	fp = fopen(name, "rb");
	if (fp == NULL){
		printf("Cannot open bitmap!\n");
		return;
	}
	fclose(fp);
	wchar_t filename[100];
	swprintf(filename, 100, L"%hs", name);
	// Load the bitmap and assign our pointer to it
	TextureImage[0] = auxDIBImageLoad(filename);

	// Just in case we want to use the width and height later
	width = TextureImage[0]->sizeX;
	height = TextureImage[0]->sizeY;

	// Generate the OpenGL texture id
	glGenTextures(1, &texture[0]);

	// Bind this texture to its id
	glBindTexture(GL_TEXTURE_2D, texture[0]);

	// Use mipmapping filter
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Generate the mipmaps
	gluBuild2DMipmaps(GL_TEXTURE_2D, 
		3, 
		TextureImage[0]->sizeX, 
		TextureImage[0]->sizeY, 
		GL_RGB, GL_UNSIGNED_BYTE, 
		TextureImage[0]->data);

	// Cleanup
	if (TextureImage[0])
	{
		if (TextureImage[0]->data)
			free(TextureImage[0]->data);

		free(TextureImage[0]);
	}
}

void GLTexture::BuildColorTexture(unsigned char r, unsigned char g, unsigned char b)
{
	unsigned char data[12];	// a 2x2 texture at 24 bits

	// Store the data
	for(int i = 0; i < 12; i += 3)
	{
		data[i] = r;
		data[i+1] = g;
		data[i+2] = b;
	}

	// Generate the OpenGL texture id
	glGenTextures(1, &texture[0]);

	// Bind this texture to its id
	glBindTexture(GL_TEXTURE_2D, texture[0]);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Use mipmapping filter
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	// Generate the texture
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, 2, 2, GL_RGB, GL_UNSIGNED_BYTE, data);
}
