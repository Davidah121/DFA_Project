#pragma once
class Box
{
public:
	Box();
	Box(int, int, int, int);
	Box(const Box & c);
	~Box();

	int x = 0;
	int y = 0;
	int width = 0;
	int height = 0;
};

