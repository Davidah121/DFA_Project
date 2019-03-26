#include "Bitmap.h"



Bitmap::Bitmap()
{
}

Bitmap::Bitmap(int width, int height)
{
	this->width = width;
	this->height = height;
	pixels = new Color[width*height];
	alphaChannel = new unsigned char[width*height];
}


Bitmap::~Bitmap()
{
	delete[] pixels;
	delete[] alphaChannel;
}

Color * Bitmap::getPixels()
{
	return pixels;
}

unsigned char * Bitmap::getAlphaChannel()
{
	return alphaChannel;
}

unsigned char * Bitmap::getPixelsAsBytes()
{
	return (unsigned char*)pixels;
}

int Bitmap::getWidth()
{
	return width;
}

int Bitmap::getHeight()
{
	return height;
}

Bitmap * Bitmap::loadBitmap(const char * filename)
{
	Bitmap* bmp = nullptr;
	
	std::fstream file = std::fstream(filename, std::fstream::in | std::fstream::binary | std::fstream::ate);
	
	if (file.is_open())
	{
		int fileSize = file.gcount();
		file.close();

		file = std::fstream(filename, std::fstream::in | std::fstream::binary);

		char* bytes = new char[fileSize];

		file.read(bytes, fileSize);
		
		file.close();

		//Assume that the file is a .bmp with the correct settings

	}
	else
	{
		//File does not exist
		file.close();
	}

	return bmp;
}
