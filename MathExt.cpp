#include "MathExt.h"

MathExt::MathExt()
{
}

MathExt::~MathExt()
{
}

int MathExt::max(int a, int b)
{
	return ((a > b) ? a : b);
}

double MathExt::max(double a, double b)
{
	return ((a > b) ? a : b);
}

float MathExt::max(float a, float b)
{
	return ((a > b) ? a : b);
}

long MathExt::max(long a, long b)
{
	return ((a > b) ? a : b);
}

int MathExt::max(int * ar, int size)
{
	int maxValue = ar[0];

	for (int i = 1; i < size; i++)
	{
		maxValue = max(ar[i], maxValue);
	}

	return maxValue;
}

double MathExt::max(double * ar, int size)
{
	double maxValue = ar[0];

	for (int i = 1; i < size; i++)
	{
		maxValue = max(ar[i], maxValue);
	}

	return maxValue;
}

float MathExt::max(float * ar, int size)
{
	float maxValue = ar[0];

	for (int i = 1; i < size; i++)
	{
		maxValue = max(ar[i], maxValue);
	}

	return maxValue;
}

long MathExt::max(long * ar, int size)
{
	long maxValue = ar[0];

	for (int i = 1; i < size; i++)
	{
		maxValue = max(ar[i], maxValue);
	}

	return maxValue;
}

int MathExt::min(int a, int b)
{
	return ((a < b) ? a : b);
}

double MathExt::min(double a, double b)
{
	return ((a < b) ? a : b);
}

float MathExt::min(float a, float b)
{
	return ((a < b) ? a : b);
}

long MathExt::min(long a, long b)
{
	return ((a < b) ? a : b);
}

int MathExt::min(int * ar, int size)
{
	int minValue = ar[0];

	for (int i = 1; i < size; i++)
	{
		minValue = min(ar[i], minValue);
	}

	return minValue;
}

double MathExt::min(double * ar, int size)
{
	double minValue = ar[0];

	for (int i = 1; i < size; i++)
	{
		minValue = min(ar[i], minValue);
	}

	return minValue;
}

float MathExt::min(float * ar, int size)
{
	float minValue = ar[0];

	for (int i = 1; i < size; i++)
	{
		minValue = min(ar[i], minValue);
	}

	return minValue;
}

long MathExt::min(long * ar, int size)
{
	long minValue = ar[0];

	for (int i = 1; i < size; i++)
	{
		minValue = min(ar[i], minValue);
	}

	return minValue;
}

float MathExt::floor(float a)
{
	return std::floorf(a);
}

float MathExt::ceil(float a)
{
	return std::ceilf(a);
}

float MathExt::round(float a)
{
	return std::roundf(a);
}

double MathExt::floor(double a)
{
	return std::floor(a);
}

double MathExt::ceil(double a)
{
	return std::ceil(a);
}

double MathExt::round(double a)
{
	return std::round(a);
}

int MathExt::sqr(int a)
{
	return a*a;
}

float MathExt::sqr(float a)
{
	return a*a;
}

double MathExt::sqr(double a)
{
	return a*a;
}

long MathExt::sqr(long a)
{
	return a*a;
}

double MathExt::sqrt(int a)
{
	return std::sqrt(a);
}

float MathExt::sqrt(float a)
{
	return std::sqrtf(a);
}

double MathExt::sqrt(double a)
{
	return std::sqrt(a);
}

int MathExt::pow(int a, int p)
{
	return std::pow(a, p);
}

long MathExt::pow(long a, long p)
{
	return std::pow(a, p);
}

float MathExt::pow(float a, float p)
{
	return std::powf(a, p);
}

double MathExt::pow(double a, double p)
{
	return std::pow(a, p);
}

int MathExt::abs(int a)
{
	return std::abs(a);
}

double MathExt::abs(double a)
{
	return std::abs(a);
}

float MathExt::abs(float a)
{
	return std::abs(a);
}

long MathExt::abs(long a)
{
	return std::abs(a);
}

int MathExt::random()
{
	return std::rand();
}

int MathExt::randomRange(int min, int max)
{
	int dis = max - min;

	int value = (rand() % dis) + min;

	return value;
}

int MathExt::clamp(int value, int min, int max)
{
	if (value <= min)
		return min;
	else if (value >= max)
		return max;
	else
		return value;
}

double MathExt::clamp(double value, double min, double max)
{
	if (value <= min)
		return min;
	else if (value >= max)
		return max;
	else
		return value;
}

float MathExt::clamp(float value, float min, float max)
{
	if (value <= min)
		return min;
	else if (value >= max)
		return max;
	else
		return value;
}

long MathExt::clamp(long value, long min, long max)
{
	if (value <= min)
		return min;
	else if (value >= max)
		return max;
	else
		return value;
}

double MathExt::sigmoid(double t)
{
	double v = 1.0 / (1.0 + MathExt::pow(2.718281828, (double)-t));

	return v;
}

float MathExt::cos(float value)
{
	return std::cosf(value);
}

double MathExt::cos(double value)
{
	return std::cos(value);
}

float MathExt::arccos(float value)
{
	return std::acosf(value);
}

double MathExt::arccos(double value)
{
	return std::acos(value);
}

float MathExt::sin(float value)
{
	return std::sinf(value);
}

double MathExt::sin(double value)
{
	return std::sin(value);
}

float MathExt::arcsin(float value)
{
	return std::asinf(value);
}

double MathExt::arcsin(double value)
{
	return std::asin(value);
}

float MathExt::tan(float value)
{
	return std::tanf(value);
}

double MathExt::tan(double value)
{
	return std::tan(value);
}

float MathExt::toDegrees(float value)
{
	return (value*180.0)/PI;
}

double MathExt::toDegrees(double value)
{
	return (value * 180.0) / PI;
}

float MathExt::toRadians(float value)
{
	return (value * PI) / 180;
}

float MathExt::toRadians(double value)
{
	return (value * PI) / 180;
}

float MathExt::arctan(float value)
{
	return std::atanf(value);
}

double MathExt::arctan(double value)
{
	return std::atan(value);
}

int MathExt::toIntColor(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
{
	//stored in RGBA
	int value = (blue << 8) + (green << 16) + (red << 24) + (alpha);
	
	return value;
}

unsigned char * MathExt::toColorArray(int color)
{
	unsigned char* colors = new unsigned char[4];
	
	colors[0] = (color >> 24) & 0xFF; // R
	colors[1] = (color >> 16) & 0xFF; // G
	colors[2] = (color >> 8) & 0xFF; // B
	colors[3] = (color >> 0) & 0xFF; // A
	//Stored in RGBA format instead of ARGB

	return colors;
}

void MathExt::setColorArray(int color, unsigned char * ar)
{
	ar[0] = (color >> 24) & 0xFF; // R
	ar[1] = (color >> 16) & 0xFF; // G
	ar[2] = (color >> 8) & 0xFF; // B
	ar[3] = (color >> 0) & 0xFF; // A
	//Stored in RGBA format instead of ARGB
}