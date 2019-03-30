#include "Bitmap.h"
#include "quickIO.h"


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

Color Bitmap::getPixel(int x, int y)
{
	return pixels[(y*width)+x];
}

Bitmap * Bitmap::loadImage(char * filename)
{
	//Assume bmp file

	char* data;
	int size = 0;
	Bitmap* temp = new Bitmap();

	quickIO file = quickIO(filename, quickIO::READ);

	if (file.isOpen())
	{
		size = file.getSize();
		data = new char[size];

		std::cout << "SIZE: " << size << std::endl;
		
		for (int i = 0; i < size; i++)
		{
			data[i] = file.readByte();
		}

		file.close();

		if (size > 0)
		{
			temp->loadBMP(data, size);
		}
	}
	
	return temp;
}

void Bitmap::loadBMP(char* fileData, int dataSize)
{
	//Assume no compression because they require being able to load
	//jpeg and png anyway.
	//Handle compression later

	int startIndex = (fileData[10]) + (fileData[11] << 8) + (fileData[12] << 16) + (fileData[13] << 24);

	width = fileData[18] & 0xFF;
	width += (fileData[19] << 8) & 0xFF00;
	width += (fileData[20] << 16) & 0xFF0000;
	width += (fileData[21] << 24) & 0xFF000000;

	height = fileData[22] & 0xFF;
	height += (fileData[23] << 8) & 0xFF00;
	height += (fileData[24] << 16) & 0xFF0000;
	height += (fileData[25] << 24) & 0xFF000000;

	if (height < 0)
		height = -height;

	pixels = new Color[width*height];
	alphaChannel = new unsigned char[width*height];

	int bpp = fileData[28] + (fileData[29] << 8); //Add support for 1, 4, 8, 16, 24, and 32. no other
	int compression = fileData[30] + (fileData[31] << 8) + (fileData[32] << 16) + (fileData[33] << 24);
	//0 = none
	//1 = run length encoding with 8 bit bitmap
	//2 = run length encoding with 4 bit bitmap
	//only focus on these later

	int colorsInPalette = 0;
	int* colorPalette = nullptr;

	colorsInPalette = fileData[46] & 0xFF;
	colorsInPalette += (fileData[47] << 8) & 0xFF00;
	colorsInPalette += (fileData[48] << 16) & 0xFF0000;
	colorsInPalette += (fileData[49] << 24) & 0xFF000000;

	//colorsInPalette = fileData[46] + (fileData[47] << 8) + (fileData[48] << 16) + (fileData[49] << 24);

	int colorPaletteIndex = 54; //start index of the color palette information

	if (colorsInPalette > 0)
	{
		colorPalette = new int[colorsInPalette];
		for (int i = 0; i < colorsInPalette; i++)
		{
			int testIndex = colorPaletteIndex + (i * 4);
			colorPalette[i] = (fileData[testIndex] << 8) & 0xFF00;
			colorPalette[i] += (fileData[testIndex + 1] << 16) & 0xFF0000;
			colorPalette[i] += (fileData[testIndex + 2] << 24) & 0xFF000000;
			colorPalette[i] += (fileData[testIndex + 3]) & 0xFF;

			//colorPalette[i] = (fileData[testIndex] << 8) + (fileData[testIndex +1] << 16) + (fileData[testIndex +2] << 24) + fileData[testIndex +3];

		}
	}

	if (bpp == 1)
	{
		//Should have a palette
		//must always be 4 byte aligned. 1x1 image takes 4 bytes still.
		int location = 7;
		int byteIndex = startIndex;
		int red, green, blue, alpha;

		int bytePadding = 4 - (width % 32) / 8;

		if ((width % 32) == 0)
		{
			bytePadding = 0;
		}

		for (int y = height - 1; y >= 0; y--)
		{
			for (int x = 0; x < width; x++)
			{
				if (colorsInPalette > 0)
				{
					int index = ((fileData[byteIndex] >> location) & 0b00000001);
					//pixels[(y*width) + x] = colorPalette[index];

				}
				else
				{
					
					red = ((fileData[byteIndex] >> location) & bpp) * 255;
					green = red;
					blue = red;
					alpha = 255;

					Color t = { red,red,red };
					alphaChannel[(y*width) + x] = 255;
					pixels[(y*width) + x] = t;
				}

				location -= bpp;
				if (location < 0)
				{
					byteIndex++;
					location = 7;
				}
			}
			location = 7;
			byteIndex += bytePadding;
		}

	}
	else if (bpp == 4)
	{
		//Must have a palette for 4 bpp.
		//must always be 4 byte aligned. 1x1 image takes 4 bytes still.
		int location = 4;
		int byteIndex = startIndex;
		int red, green, blue, alpha;
		alpha = 255;

		int bytePadding = 4 - MathExt::floor((float)(width % 32) / 2);

		if ((width % 8) == 0)
		{
			bytePadding = 0;
		}

		for (int y = height - 1; y >= 0; y--)
		{
			for (int x = 0; x < width; x++)
			{
				if (colorsInPalette > 0)
				{
					int index = ((fileData[byteIndex] >> location) & 0b00001111);
					//pixels[(y*width) + x] = colorPalette[index];
				}
				else
				{
					//Assume this does not happen
				}

				location -= bpp;
				if (location < 0)
				{
					byteIndex++;
					location = 4;
				}
			}

			location = 4;
			byteIndex += bytePadding;
		}
	}
	else if (bpp == 8)
	{
		//There should be a palette for 8 bpp, but not always
		//Assume no alpha.
		//Assume green and blue take presidence over red.
		//must always be 4 byte aligned. 1x1 image takes 4 bytes still.

		int byteIndex = startIndex;
		int red, blue, green, alpha;
		alpha = 255;

		int bytePadding = 4 - (width % 4);

		if ((width % 4) == 0)
		{
			bytePadding = 0;
		}

		for (int y = height - 1; y >= 0; y--)
		{
			for (int x = 0; x < width; x++)
			{
				if (colorsInPalette > 0)
				{
					int index = fileData[byteIndex];

					//pixels[(y*width) + x] = colorPalette[index];
				}
				else
				{
					int byte = fileData[byteIndex];
					blue = (int)((255.0 / 3.0) * (byte & 3));
					green = (int)((255.0 / 7.0) * ((byte >> 2) & 7));
					red = (int)((255.0 / 7.0) * ((byte >> 5) & 7));

					Color t = { blue, green, red };
					alphaChannel[(y*width) + x] = 255;
					pixels[(y*width) + x] = t;

				}
				//pixels[i] = (red << 24) + (green << 16) + (blue << 8) + alpha;
				byteIndex++;
			}

			byteIndex += bytePadding;
		}
	}
	else if (bpp == 16)
	{
		//Assume alpha.
		//If no alpha, Assume green take presidence over red and blue.
		//must always be 4 byte aligned. 1x1 image takes 4 bytes still.

		int byteIndex = startIndex;
		int red, blue, green, alpha;
		alpha = 255;

		for (int y = height - 1; y >= 0; y--)
		{
			for (int x = 0; x < width; x++)
			{
				if (colorsInPalette > 0)
				{
					int index = fileData[byteIndex] + (fileData[byteIndex] << 8);

					//pixels[(y*width) + x] = colorPalette[index];
				}
				else
				{
					/*
					//If no alpha
					int byte = fileData[byteIndex] + (fileData[byteIndex]<<8);
					blue = (int)((255.0 / 31) * (byte & 31));
					green = (int)((255.0 / 63) * ((byte >> 5) & 63));
					red = (int)((255.0 / 31) * ((byte >> 11) & 31));
					*/

					//If alpha
					int byte = fileData[byteIndex] + (fileData[byteIndex] << 8);
					blue = (int)((255.0 / 31) * (byte & 31));
					green = (int)((255.0 / 31) * ((byte >> 5) & 31));
					red = (int)((255.0 / 31) * ((byte >> 10) & 31));
					alpha = (int)((255.0 / 31) * ((byte >> 15) & 31));


					Color t = { blue, green, red };
					alphaChannel[(y*width) + x] = alpha;
					pixels[(y*width) + x] = t;
				}
				//pixels[i] = (red << 24) + (green << 16) + (blue << 8) + alpha;
				byteIndex += 2;
			}
		}
	}
	else if (bpp == 24)
	{
		std::cout << "24 bits" << std::endl;
		//Assume no alpha.
		//Assume no palette.
		//must always be 4 byte aligned. 1x1 image takes 4 bytes still.

		int byteIndex = startIndex;
		int red, blue, green, alpha;
		alpha = 255;

		int bytePadding = (width % 4);

		if ((width % 4) == 0)
		{
			bytePadding = 0;
		}

		for (int y = height - 1; y >= 0; y--)
		{
			for (int x = 0; x < width; x++)
			{
				if (colorsInPalette > 0)
				{
					//int index = fileData[byteIndex];
					//pixels[i] = colorPalette[index];
				}
				else
				{
					blue = (fileData[byteIndex]);
					green = (fileData[byteIndex + 1]);
					red = (fileData[byteIndex + 2]);
					//alpha = (fileData[byteIndex + 3]) & 0xFF;

					Color t = { blue, green, red };
					alphaChannel[(y*width) + x] = 255;
					pixels[(y*width) + x] = t;
					//pixels[(y*width) + x] = red + green + blue + alpha;
				}
				byteIndex += 3;
			}
			byteIndex += bytePadding;
		}
	}
	else if (bpp == 32)
	{
		//Assume alpha.
		//Assume no palette.
		//must always be 4 byte aligned. 1x1 image takes 4 bytes still.

		int byteIndex = startIndex;
		int red, blue, green, alpha;
		alpha = 255;

		for (int y = height - 1; y >= 0; y--)
		{
			for (int x = 0; x < width; x++)
			{
				if (colorsInPalette > 0)
				{
					//int index = fileData[byteIndex];
					//pixels[i] = colorPalette[index];
				}
				else
				{
					blue = (fileData[byteIndex]);
					green = (fileData[byteIndex + 1]);
					red = (fileData[byteIndex + 2]);
					alpha = (fileData[byteIndex + 3]);

					Color t = { blue, green, red };
					alphaChannel[(y*width) + x] = alpha;
					pixels[(y*width) + x] = t;
					//pixels[(y*width) + x] = red + green + blue + alpha;
				}
				byteIndex += 4;
			}
		}
	}
}