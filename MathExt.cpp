#include "MathExt.h"



MathExt::MathExt()
{
}


MathExt::~MathExt()
{
}

int MathExt::clamp(int value, int min, int max)
{
	if (value >= max)
		return max;
	else if (value <= min)
		return min;
	else
		return value;
}

float MathExt::clamp(float value, float min, float max)
{
	if (value >= max)
		return max;
	else if (value <= min)
		return min;
	else
		return value;
}

double MathExt::clamp(double value, double min, double max)
{
	if (value >= max)
		return max;
	else if (value <= min)
		return min;
	else
		return value;
}

long MathExt::clamp(long value, long min, long max)
{
	if (value >= max)
		return max;
	else if (value <= min)
		return min;
	else
		return value;
}
