#pragma once
#include <Windows.h>
#include <fstream>

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

	static Bitmap* loadBitmap(const char* filename);

private:
	int width = 0;
	int height = 0;
	Color* pixels;
	unsigned char* alphaChannel;
};

