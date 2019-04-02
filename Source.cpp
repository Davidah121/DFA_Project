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
	Renderer::drawLine(64, 64, 196, 196);

	Renderer::setDrawColor(Color{ 255,255,255 });
	//Renderer::drawRect(0, 0, 128, 128);
	
	Renderer::drawCircle(64, 64, 28);
	Renderer::drawCircle(196, 64, 28);
	Renderer::drawCircle(196, 196, 28);
	Renderer::drawCircle(64, 196, 28);

	
	//Renderer::drawImage(myFont.getFontImage(), 0, 0);
	
	Renderer::setDrawColor(Color{ 0, 0, 255 });
	Renderer::drawText("Q1", 64 - 16, 64 - 16);
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
	
	return 0;
}