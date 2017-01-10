/**
 The bitmap's id must be surrounded by quotation marks (i.e. "Texture.bmp").

 Usage:
 GLTexture tex;
 GLTexture tex3;

 tex.Load("texture.bmp");             // Loads a bitmap
 tex.Use();				              // Binds the bitmap for use

 // You can also build a texture with a single color and use it
 tex3.BuildColorTexture(255, 0, 0);	  // Builds a solid red texture
 tex3.Use();				          // Binds the targa for use

 */

#ifndef GLTEXTURE_H
#define GLTEXTURE_H

#include "prefix.h"
#include "data_struct.h"

class GLTexture  
{
private:
	char *texturename;								// The textures name
	unsigned int texture[1];						// OpenGL's number for the texture
	int width;										// Texture's width
	int height;										// Texture's height
public:
	GLTexture();									// Constructor
	void mount();									// Binds the texture for use
	void unmount();									// unmount the texture being used
	void BuildColorTexture(unsigned char r, unsigned char g, unsigned char b);	// Sometimes we want a texture of uniform color
	void LoadBMP(char *name);						// Loads a bitmap file
	void Load(char *name);							// Load the texture
	virtual ~GLTexture();							// Destructor
};

#endif
