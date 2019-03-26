#pragma once
#include <math.h>

class MathExt
{
public:
	MathExt();
	~MathExt();

	static int clamp(int value, int min, int max);
	static float clamp(float value, float min, float max);
	static double clamp(double value, double min, double max);
	static long clamp(long value, long min, long max);

};

