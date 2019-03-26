#pragma once
#include "Bitmap.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	static void bindImage(Bitmap* img);
	static void clear();

	static void setDrawColor(Color v);

	static void drawRect(int x, int y, int width, int height);
	static void drawImage(Bitmap* img, int x, int y);
	static void drawImagePart(Bitmap* img, int x, int y, int leftCull, int topCull, int widthCull, int heightCull);
private:
	static Bitmap* bindedImage;
	static Color drawColor;
};

