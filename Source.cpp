#include <iostream>
#include "WndWindow.h"
#include "System.h"
#include "Bitmap.h"
#include "Renderer.h"
#include "BMPFont.h"
#include "DFA.h"

Bitmap* img;
BMPFont myFont = BMPFont("newFont");
DFA* dfaTest = nullptr;
std::string procString = "";

int index = -1;
int timePassed = 0;
bool tock = false;

void paintFunc()
{
	Renderer::bindImage(img);
	Renderer::setDrawColor(Color{ 121,77,49 });
	Renderer::clear();

	if (index == -1)
	{
		dfaTest->drawDFA();
	}
	else
	{
		dfaTest->processStringInteractive(procString, index);
		if (tock == true)
		{
			std::string tempText = "";
			tempText += procString[index];

			Renderer::setDrawColor(Color{ 255,255,255 });
			Renderer::drawText(tempText, 0, 0);
		}
	}

	Renderer::setDrawColor(Color{ 255,255,255 });
	Renderer::drawText(procString, 320, 0);

	timePassed++;

	if (timePassed > 45)
	{
		tock = false;
	}
	if (timePassed > 60)
	{
		timePassed = 0;
		tock = true;
		index++;

		if (index > procString.size())
		{
			index = procString.size();
		}
	}


}

int main(int argc, char** argv)
{
	if (argc > 2)
	{
		dfaTest = new DFA(argv[1]);
		procString = argv[2];

		WndWindow wnd(640, 480, "DFA");

		img = wnd.getImage();
		Renderer::bindFont(&myFont);

		wnd.setPaintFunction(paintFunc);

		while (wnd.getRunning())
		{
			wnd.repaint();
			System::sleepMicros(16666);
		}
		
		if (dfaTest->processString(procString))
		{
			std::cout << procString << " was accepted" << std::endl;
		}
		else
		{
			std::cout << procString << " was not accepted" << std::endl;
		}
	}
	else
	{
		std::cout << "Not enough arguments were provided" << std::endl;
	}
	return 0;
}