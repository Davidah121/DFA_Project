#include "System.h"



System::System()
{
}


System::~System()
{
}

long System::getTimeNano()
{
	std::chrono::high_resolution_clock::duration d = std::chrono::high_resolution_clock::now().time_since_epoch();
	return std::chrono::duration_cast<std::chrono::nanoseconds>(d).count();
}

long System::getTimeMicro()
{
	std::chrono::high_resolution_clock::duration d = std::chrono::high_resolution_clock::now().time_since_epoch();
	return std::chrono::duration_cast<std::chrono::microseconds>(d).count();
}

long System::getTimeMilli()
{
	std::chrono::high_resolution_clock::duration d = std::chrono::high_resolution_clock::now().time_since_epoch();
	return std::chrono::duration_cast<std::chrono::milliseconds>(d).count();
}

void System::sleepMicros(int micros)
{
	long startTime = getTimeMicro();

	while (true)
	{
		if (getTimeMicro() - startTime >= micros)
		{
			break;
		}
	}
}

void System::sleepMillis(int millis)
{
	long startTime = getTimeMilli();

	while (true)
	{
		if (getTimeMilli() - startTime >= millis)
		{
			break;
		}
	}
}