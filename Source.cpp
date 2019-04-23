#include <iostream>
#include "WndWindow.h"
#include "System.h"
#include "Bitmap.h"
#include "Renderer.h"
#include "BMPFont.h"
#include "DFA.h"

#define PI 3.1415926

Bitmap* img;
BMPFont myFont = BMPFont("newFont");
DFA dfaTest = DFA((char*)"DFA_Test.txt");

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
	Renderer::setDrawColor(Color{ 121,77,49 });
	Renderer::clear();

	dfaTest.drawDFA();
	/*
	Renderer::setDrawColor(Color{ 255, 0, 255 });
	BezierCurve q = BezierCurve();
	q.addPoint(Vec2f(36+8, 64));
	q.addPoint(Vec2f(36+8, 0));
	q.addPoint(Vec2f(92-8, 0));
	q.addPoint(Vec2f(92-8, 64));


	Renderer::setDrawColor(Color{ 255,255,0 });
	Renderer::drawBezierCurve(q);

	Renderer::setDrawColor(Color{ 255,255,255 });
	
	Renderer::drawCircle(64, 64, 28);
	Renderer::drawCircle(196, 64, 28);
	Renderer::drawCircle(196, 196, 28);
	Renderer::drawCircle(64, 196, 28);

	
	//Renderer::drawImage(myFont.getFontImage(), 0, 0);
	
	Renderer::setDrawColor(Color{ 0, 0, 255 });
	Renderer::drawText("Q1", 64-16, 64-8);
	Renderer::drawText("Q2", 196-16, 64-8);
	Renderer::drawText("Q3", 196-16, 196-8);
	Renderer::drawText("Q4", 64-16, 196-8);

	Renderer::drawText("a", 64, 0);
	*/
}

int main()
{
	WndWindow wnd(640, 480, "TITLE");
	
	img = wnd.getImage();
	Renderer::bindFont(&myFont);

	wnd.setMouseButtonDownFunction(dbCLK);
	wnd.setPaintFunction(paintFunc);

	
	while (wnd.getRunning())
	{
		wnd.repaint();
		System::sleepMicros(16666);
	}
	
	return 0;
}