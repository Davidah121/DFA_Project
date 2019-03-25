#include <iostream>
#include "WndWindow.h"
#include "System.h"

void dbCLK(int but)
{
	if (but == WndWindow::MOUSE_LEFT)
	{
		std::cout << "LEFT CLICK" << std::endl;
	}
}

int main()
{
	WndWindow wnd("TITLE");

	wnd.setMouseButtonDownFunction(dbCLK);

	/*
	while (wnd.getRunning())
	{

	}
	*/
	return 0;
}