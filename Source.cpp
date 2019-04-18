#include <iostream>
#include "WndWindow.h"
#include "System.h"
#include "Bitmap.h"
#include "Renderer.h"
#include "BMPFont.h"

#define PI 3.1415926

Bitmap* img;
BMPFont myFont = BMPFont("test1");

int deg = 0;
int x = 0;
double t = 0;

void dbCLK(int but)
{
	if (but == WndWindow::MOUSE_LEFT)
	{
		std::cout << "LEFT CLICK" << std::endl;
	}
}

void paintFunc()
{
	Renderer::bindImage(img);
	Renderer::setDrawColor(Color{ 0,0,0 });
	Renderer::clear();

	Renderer::setDrawColor(Color{ 255, 0, 255 });
	BezierCurve q = BezierCurve();
	q.addPoint(Vec2f(196, 64));
	q.addPoint(Vec2f(130, 32));
	q.addPoint(Vec2f(64, 64));

	BezierCurve q2 = BezierCurve();
	q2.addPoint(Vec2f(196, 64));
	q2.addPoint(Vec2f(130, 96));
	q2.addPoint(Vec2f(64, 64));

	BezierCurve q3 = BezierCurve();
	q3.addPoint(Vec2f(196, 64));
	q3.addPoint(Vec2f(130, 16));
	q3.addPoint(Vec2f(64, 64));

	BezierCurve q4 = BezierCurve();
	q4.addPoint(Vec2f(196, 64));
	q4.addPoint(Vec2f(130, 112));
	q4.addPoint(Vec2f(64, 64));

	Renderer::setDrawColor(Color{ 255,255,0 });
	Renderer::drawBezierCurve(q);
	Renderer::drawBezierCurve(q4);

	Renderer::setDrawColor(Color{ 0,255,255 });
	Renderer::drawBezierCurve(q2);
	Renderer::drawBezierCurve(q3);

	Renderer::setDrawColor(Color{ 255,255,255 });
	
	Renderer::drawCircle(64, 64, 28);
	Renderer::drawCircle(196, 64, 28);
	Renderer::drawCircle(196, 196, 28);
	Renderer::drawCircle(64, 196, 28);

	
	//Renderer::drawImage(myFont.getFontImage(), 0, 0);
	
	Renderer::setDrawColor(Color{ 0, 0, 255 });
	Renderer::drawText("Q123", 64 - 16, 64 - 16);
	Renderer::drawText("Q2", 196 - 16, 64 - 16);
	Renderer::drawText("Q3", 196 - 16, 196 - 16);
	Renderer::drawText("Q4", 64 - 16, 196 - 16);
	
}

int main()
{
	
	WndWindow wnd(1280, 720, "TITLE");
	
	img = wnd.getImage();
	Renderer::bindFont(&myFont);

	wnd.setMouseButtonDownFunction(dbCLK);
	wnd.setPaintFunction(paintFunc);

	
	while (wnd.getRunning())
	{
		wnd.repaint();
		System::sleepMicros(16666);
	}
	
	system("pause");
	return 0;
}