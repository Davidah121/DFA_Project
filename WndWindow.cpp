#include "WndWindow.h"
#include <iostream>

std::vector<WndWindow*> WndWindow::windowList = std::vector<WndWindow*>();
int WndWindow::screenWidth = GetSystemMetrics(SM_CXFULLSCREEN);
int WndWindow::screenHeight = GetSystemMetrics(SM_CYFULLSCREEN);

WndWindow * WndWindow::getWindowByHandle(HWND handle)
{
	for (int i = 0; i < windowList.size(); i++)
	{
		if (handle == windowList[i]->getWindowHandle())
		{
			return windowList[i];
		}
	}

	return nullptr;
}

void WndWindow::removeWindowFromList(WndWindow* wnd)
{
	int swapIndex = -1;

	for (int i = 0; i < windowList.size(); i++)
	{
		if (wnd == windowList[i])
		{
			swapIndex = i;
		}
	}

	if (swapIndex != -1)
	{
		windowList[swapIndex] = windowList[windowList.size() - 1];
		windowList.pop_back();
	}
}
LRESULT _stdcall WndWindow::wndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	WndWindow* currentWindow = WndWindow::getWindowByHandle(hwnd);

	bool canDo = false;

	if (currentWindow != nullptr)
	{
		switch (msg)
		{
		case WM_PAINT:
			if (currentWindow->paintFunction != nullptr)
				currentWindow->paintFunction();
			break;
		case WM_CLOSE:
			//currentWindow->dispose();
			break;
		case WM_DESTROY:
			if (currentWindow->closingFunction != nullptr)
				currentWindow->closingFunction();
			PostQuitMessage(0);
			currentWindow->setRunning(false);
			break;
		case WM_KEYDOWN:
			if (currentWindow->keyDownFunction != nullptr)
				currentWindow->keyDownFunction(wparam, lparam);
			break;
		case WM_KEYUP:
			if (currentWindow->keyUpFunction != nullptr)
				currentWindow->keyUpFunction(wparam, lparam);
			break;
		case WM_LBUTTONDOWN:
			if (currentWindow->mouseButtonDownFunction != nullptr)
				currentWindow->mouseButtonDownFunction(MOUSE_LEFT);
			break;
		case WM_MBUTTONDOWN:
			if (currentWindow->mouseButtonDownFunction != nullptr)
				currentWindow->mouseButtonDownFunction(MOUSE_MIDDLE);
			break;
		case WM_RBUTTONDOWN:
			if (currentWindow->mouseButtonDownFunction != nullptr)
				currentWindow->mouseButtonDownFunction(MOUSE_RIGHT);
			break;
		case WM_LBUTTONUP:
			if (currentWindow->mouseButtonUpFunction != nullptr)
				currentWindow->mouseButtonUpFunction(MOUSE_LEFT);
			break;
		case WM_MBUTTONUP:
			if (currentWindow->mouseButtonUpFunction != nullptr)
				currentWindow->mouseButtonUpFunction(MOUSE_MIDDLE);
			break;
		case WM_RBUTTONUP:
			if (currentWindow->mouseButtonUpFunction != nullptr)
				currentWindow->mouseButtonUpFunction(MOUSE_RIGHT);
			break;
		case WM_MOUSEWHEEL:
			if (currentWindow->mouseWheelFunction != nullptr)
				currentWindow->mouseWheelFunction((wparam >> 16));
		case WM_MOUSEHWHEEL:
			if (currentWindow->mouseHWheelFunction != nullptr)
				currentWindow->mouseHWheelFunction((wparam >> 16));
		case WM_MOUSEMOVE:
			if (currentWindow->mouseMovedFunction != nullptr)
				currentWindow->mouseMovedFunction();
		default:
			break;
		}
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

WndWindow::WndWindow()
{
	x = screenWidth / 2 - 160;
	y = screenHeight / 2 - 120;
	width = 320;
	height = 240;
	title = "";

	wndThread = new std::thread(&WndWindow::init, this, x, y, width, height, title);

	//init(x,y,width,height,title);
}

WndWindow::WndWindow(const char* title)
{
	x = screenWidth / 2 - 160;
	y = screenHeight / 2 - 120;
	width = 320;
	height = 240;
	this->title = title;

	wndThread = new std::thread(&WndWindow::init, this, x, y, width, height, title);

	//init(x,y,width,height,title);
}

WndWindow::WndWindow(int width, int height, const char* title)
{
	x = screenWidth / 2 - width/2;
	y = screenHeight / 2 - height/2;
	this->width = width;
	this->height = height;
	this->title = title;

	wndThread = new std::thread(&WndWindow::init, this, x, y, width, height, title);

	//init(x,y,width,height,title);
}

WndWindow::WndWindow(int x, int y, int width, int height, const char* title)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->title = title;

	wndThread = new std::thread(&WndWindow::init, this, x, y, width, height, title);

	//init(x,y,width,height,title);
}


WndWindow::~WndWindow()
{
	dispose();
}

void WndWindow::dispose()
{
	if (getValid())
	{
		std::string text = title;
		text += "_CLASS";

		setRunning(false);
		setValid(false);

		if (wndThread != nullptr)
		{
			if (wndThread->joinable())
				wndThread->join();
		}

		if (IsWindow(windowHandle))
		{
			CloseWindow(windowHandle);
			DestroyWindow(windowHandle);
		}
		UnregisterClass(text.c_str(), hins);

		WndWindow::removeWindowFromList(this);

		std::cout << "DISPOSING" << std::endl;
	}
}

void WndWindow::init(int x, int y, int width, int height, const char * title)
{
	std::string text = title;
	text += "_CLASS";

	hins = GetModuleHandle(NULL);

	wndClass.cbClsExtra = 0;
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)(BLACK_BRUSH);
	wndClass.hCursor = LoadCursor(hins, IDC_ARROW);
	wndClass.hIcon = LoadIcon(hins, IDI_APPLICATION);
	wndClass.hIconSm = LoadIcon(hins, IDI_APPLICATION);
	wndClass.hInstance = hins;
	wndClass.lpfnWndProc = WndWindow::wndProc;
	wndClass.lpszClassName = text.c_str();
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	if(RegisterClassEx(&wndClass)!=NULL)
	{
		windowHandle = CreateWindowEx(NULL, text.c_str(), title, WS_OVERLAPPEDWINDOW, x, y, width+16, height+40, NULL, NULL, hins, NULL);

		if (windowHandle!=NULL)
		{
			setVisible(true);
			setValid(true);
			setRunning(true);

			WndWindow::windowList.push_back(this);

			run();
		}
		else
		{
			//dispose
			//The class registered, but the window creation failed
			UnregisterClass(text.c_str(), hins);
			setValid(false);
			setRunning(false);
			std::cout << "Failed window creation" << std::endl;
		}
	}
	else
	{
		//dispose
		//Nothing because the window wasn't created and the
		//class failed to register
		setValid(false);
		setRunning(false);
		std::cout << "Failed class creation" << std::endl;
		std::cout << GetLastError() << std::endl;
	}
	
}

void WndWindow::setRunning(bool value)
{
	myMutex.lock();
	running = value;
	myMutex.unlock();
}

bool WndWindow::getRunning()
{
	bool v = true;
	myMutex.lock();
	v = running;
	myMutex.unlock();

	return v;
}

void WndWindow::setValid(bool value)
{
	myMutex.lock();
	valid = value;
	myMutex.unlock();
}

void WndWindow::setVisible(bool value)
{
	if (value == true)
		ShowWindow(windowHandle, SW_SHOW);
	else
		ShowWindow(windowHandle, SW_HIDE);
}

void WndWindow::setX(int x)
{
	SetWindowPos(windowHandle, HWND_TOP, x, this->y, this->width, this->height, SWP_ASYNCWINDOWPOS | SWP_NOREDRAW);
}

void WndWindow::setY(int y)
{
	SetWindowPos(windowHandle, HWND_TOP, this->x, y, this->width, this->height, SWP_ASYNCWINDOWPOS | SWP_NOREDRAW);
}

void WndWindow::setPosition(int x, int y)
{
	SetWindowPos(windowHandle, HWND_TOP, x, y, this->width, this->height, SWP_ASYNCWINDOWPOS | SWP_NOREDRAW);
}

void WndWindow::setWidth(int width)
{
	SetWindowPos(windowHandle, HWND_TOP, this->x, this->y, width, this->height, SWP_ASYNCWINDOWPOS | SWP_NOREDRAW);
}

void WndWindow::setHeight(int height)
{
	SetWindowPos(windowHandle, HWND_TOP, this->x, this->y, this->width, height, SWP_ASYNCWINDOWPOS | SWP_NOREDRAW);
}

void WndWindow::setSize(int width, int height)
{
	SetWindowPos(windowHandle, HWND_TOP, this->x, this->y, width, height, SWP_ASYNCWINDOWPOS | SWP_NOREDRAW);
}

bool WndWindow::getValid()
{
	bool value = true;

	myMutex.lock();
	value = this->valid;
	myMutex.unlock();

	return value;
}

HWND WndWindow::getWindowHandle()
{
	return windowHandle;
}

void WndWindow::setPaintFunction(void(*function)(void))
{
	paintFunction = function;
}

void WndWindow::setKeyUpFunction(void(*function)(WPARAM, LPARAM))
{
	keyUpFunction = function;
}

void WndWindow::setKeyDownFunction(void(*function)(WPARAM, LPARAM))
{
	keyDownFunction = function;
}

void WndWindow::setMouseButtonDownFunction(void(*function)(int))
{
	mouseButtonDownFunction = function;
}

void WndWindow::setMouseButtonUpFunction(void(*function)(int))
{
	mouseButtonUpFunction = function;
}

void WndWindow::setMouseHWheelFunction(void(*function)(int))
{
	mouseHWheelFunction = function;
}

void WndWindow::setMouseWheelFunction(void(*function)(int))
{
	mouseWheelFunction = function;
}

void WndWindow::setMouseButtonMovedFunction(void(*function)(void))
{
	mouseMovedFunction = function;
}

void WndWindow::setClosingFunction(void(*function)(void))
{
	closingFunction = function;
}

void WndWindow::run()
{
	while (getRunning())
	{
		MSG m;
		ZeroMemory(&m, sizeof(MSG));

		while (PeekMessage(&m, windowHandle, NULL, NULL, PM_REMOVE))
		{
			TranslateMessage(&m);
			DispatchMessage(&m);
		}
	}
}