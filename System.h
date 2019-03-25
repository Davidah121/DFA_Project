#pragma once
#include <chrono>

class System
{
public:
	System();
	~System();

	static long getTimeNano();
	static long getTimeMicro();
	static long getTimeMilli();

	static void sleepMicros(int micros);
	static void sleepMillis(int millis);
};

