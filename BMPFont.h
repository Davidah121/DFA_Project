#pragma once
#include <vector>
#include "Bitmap.h"
#include "Box.h"

class BMPFont
{
public:
	BMPFont(const char* filename);
	~BMPFont();

	Box getCharInfo(unsigned char c);
	Bitmap* getFontImage();
	int getFontSize();

private:
	void loadStuff(const char* filename);

	Bitmap* fontImage = nullptr;
	int fontSize = 0;

	std::vector<Box> fontInfo = std::vector<Box>();
};

