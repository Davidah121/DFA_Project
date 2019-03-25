#pragma once
#include <Windows.h>
#include <thread>
#include <vector>
#include <mutex>

class WndWindow
{
public:
	static const int MOUSE_LEFT = 0;
	static const int MOUSE_MIDDLE = 1;
	static const int MOUSE_RIGHT = 2;

	WndWindow();
	WndWindow(const char* title);
	WndWindow(int width, int height, const char* title);
	WndWindow(int x, int y, int width, int height, const char* title);
	~WndWindow();

	void setVisible(bool value);

	void setX(int x);
	void setY(int y);
	void setPosition(int x, int y);

	void setWidth(int width);
	void setHeight(int height);
	void setSize(int width, int height);

	bool getValid();
	bool getRunning();

	HWND getWindowHandle();

	void setPaintFunction(void(*function)(void));
	void setKeyUpFunction(void(*function)(WPARAM, LPARAM));
	void setKeyDownFunction(void(*function)(WPARAM, LPARAM));

	void setMouseButtonDownFunction(void(*function)(int));
	void setMouseButtonUpFunction(void(*function)(int));
	void setMouseHWheelFunction(void(*function)(int));
	void setMouseWheelFunction(void(*function)(int));
	void setMouseButtonMovedFunction(void(*function)(void));

	void setClosingFunction(void(*function)(void));

private:

	static std::vector<WndWindow*> windowList;
	static int screenWidth;
	static int screenHeight;
	static WndWindow* getWindowByHandle(HWND value);
	static void removeWindowFromList(WndWindow* value);
	static LRESULT _stdcall wndProc(HWND hwnd, UINT uint, WPARAM wparam, LPARAM lparam);

	void init(int x, int y, int width, int height, const char* title);
	
	void setRunning(bool value);
	void setValid(bool value);
	void run();
	void dispose();
	
	int x = 0;
	int y = 0;
	int width = 320;
	int height = 240;
	const char* title = "";

	std::thread* wndThread;
	std::mutex myMutex;

	HWND windowHandle;
	WNDCLASSEX wndClass;
	HINSTANCE hins;

	bool valid = true;
	bool running = true;

	void (*paintFunction)(void);
	void (*keyUpFunction)(WPARAM, LPARAM);
	void (*keyDownFunction)(WPARAM, LPARAM);

	void(*mouseDoubleClickFunction)(int);
	void(*mouseButtonDownFunction)(int);
	void(*mouseButtonUpFunction)(int);
	void(*mouseWheelFunction)(int);
	void(*mouseHWheelFunction)(int);
	void(*mouseMovedFunction)(void);

	void (*closingFunction)(void);
};
