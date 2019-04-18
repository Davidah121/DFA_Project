#pragma once
#include<cmath>

#undef max
#undef min

#define PI 3.1415927
#define E 2.718281828459

class MathExt
{
public:
	MathExt();
	~MathExt();

	static int max(int a, int b);
	static double max(double a, double b);
	static float max(float a, float b);
	static long max(long a, long b);

	static int max(int* ar, int size);
	static double max(double* ar, int size);
	static float max(float* ar, int size);
	static long max(long* ar, int size);

	static int min(int a, int b);
	static double min(double a, double b);
	static float min(float a, float b);
	static long min(long a, long b);

	static int min(int* ar, int size);
	static double min(double* ar, int size);
	static float min(float* ar, int size);
	static long min(long* ar, int size);
	
	static float floor(float a);
	static float ceil(float a);
	static float round(float a);

	static double floor(double a);
	static double ceil(double a);
	static double round(double a);

	static int sqr(int a);
	static float sqr(float a);
	static double sqr(double a);
	static long sqr(long a);
	
	static double sqrt(int a);
	static float sqrt(float a);
	static double sqrt(double a);

	static int pow(int a, int p);
	static long pow(long a, long p);
	static float pow(float a, float p);
	static double pow(double a, double p);

	static int abs(int a);
	static double abs(double a);
	static float abs(float a);
	static long abs(long a);

	static int random();
	static int randomRange(int min, int max);
	
	static int clamp(int value, int min, int max);
	static float clamp(float value, float min, float max);
	static double clamp(double value, double min, double max);
	static long clamp(long value, long min, long max);

	static double sigmoid(double t);

	static float cos(float value);
	static double cos(double value);

	static float sin(float value);
	static double sin(double value);
	
	static float tan(float value);
	static double tan(double value);

	static float toDegrees(float value);
	static double toDegrees(double value);

	static float toRadians(float value);
	static float toRadians(double value);

	static float arccos(float value);
	static double arccos(double value);

	static float arcsin(float value);
	static double arcsin(double value);

	static float arctan(float value);
	static double arctan(double value);

	static int toIntColor(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);
	static unsigned char* toColorArray(int color);
	static void setColorArray(int color, unsigned char* ar);
};

