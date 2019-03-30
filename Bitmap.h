#pragma once
#include <Windows.h>
#include <fstream>
#include "MathExt.h"

struct Color {
	unsigned char b;
	unsigned char g;
	unsigned char r;
};

class Bitmap
{
public:
	Bitmap();
	Bitmap(int width, int height);
	~Bitmap();

	Color* getPixels();
	unsigned char* getAlphaChannel();

	unsigned char* getPixelsAsBytes();

	int getWidth();
	int getHeight();

	Color getPixel(int x, int y);

	static Bitmap* loadImage(char* filename);

private:
	int width = 0;
	int height = 0;
	Color* pixels;
	
	unsigned char* alphaChannel;

	void loadBMP(char* data, int size);
};

