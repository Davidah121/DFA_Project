#pragma once
#include "Bitmap.h"
#include "BMPFont.h"
#include "BezierCurve.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	static void bindImage(Bitmap* img);
	static void bindFont(BMPFont* font);

	static Bitmap* getBindedImage();
	static BMPFont* getBindedFont();

	static void clear();

	static void setDrawColor(Color v);

	static void drawLine(int x1, int y1, int x2, int y2);
	static void drawRectOutline(int x, int y, int width, int height);
	static void drawRect(int x, int y, int width, int height);
	static void drawCircle(int x, int y, int radius);

	static void drawBezierCurve(BezierCurve v);
	static void drawImage(Bitmap* img, int x, int y);
	static void drawImagePart(Bitmap* img, int x, int y, int leftCull, int topCull, int rightCull, int bottomCull);

	static void drawText(std::string s, int x, int y);
	//static void drawText(const char* s, int x, int y);

private:
	static Bitmap* bindedImage;
	static Color drawColor;
	static BMPFont* bindedFont;
};

