#include <iostream>
#include "WndWindow.h"
#include "System.h"
#include "Bitmap.h"
#include "Renderer.h"

#define PI 3.1415926

Bitmap* img;

int deg = 0;
int x = 0;

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

	Renderer::setDrawColor(Color{ 255,255,255 });

	
	Renderer::drawRect(160+(cos(PI*deg/180)*16) + x, 120+(sin(PI*deg/180)*16), 32, 32);

	x += 2;
	deg+=5;

	if (deg >= 360)
		deg = 0;
	
}

int main()
{
	WndWindow wnd("TITLE");

	img = wnd.getImage();

	wnd.setMouseButtonDownFunction(dbCLK);
	wnd.setPaintFunction(paintFunc);

	
	while (wnd.getRunning())
	{
		wnd.repaint();
		System::sleepMicros(16666);
	}
	
	return 0;
}