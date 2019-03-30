#pragma once
#include<iostream>
#include<string>
#include <io.h>
#include<fcntl.h>
#include <vector>

class stringTools
{
public:
	stringTools();
	~stringTools();

	static void init();

	static wchar_t* toWideString(char* text);
	static wchar_t* toWideString(const char* text);

	static char* toCString(wchar_t* text);
	static char* toCString(const wchar_t* text);

	static int stringLength(char* text);
	static int stringLength(wchar_t* text);

	static int stringLength(const char* text);
	static int stringLength(const wchar_t* text);

	static char* pointerToString(void* location);

	static char* toHexString(char value);
	static char* toHexString(short value);
	static char* toHexString(int value);
	static char* toHexString(long value);

	static std::wstring getWideString();
	static std::string getString();

	static char getChar();
	static wchar_t getWideChar();
	static int getInt();

	static std::vector<std::string> splitString(std::string s, char delim);
	static std::vector<std::string> splitString(std::string s, char* delim);

	static int toInt(std::string s);
	static long toLong(std::string s);
	static double toDouble(std::string s);
	static float toFloat(std::string s);

	static void print(char text);
	static void println(char text);

	static void print(wchar_t text);
	static void println(wchar_t text);

	static void print(char* text);
	static void println(char* text);

	static void print(wchar_t* text);
	static void println(wchar_t* text);

	static void print(std::string text);
	static void println(std::string text);

	static void print(std::wstring text);
	static void println(std::wstring text);

	static void print(int text);
	static void println(int text);

	static void print(float text);
	static void println(float text);

	static void print(double text);
	static void println(double text);

	static void print(long text);
	static void println(long text);

	static void print(void* t);
	static void println(void* t);

	static std::wostream out;
	static std::wistream in;

	static std::wostream err;
	static const wchar_t lineBreak;

	static void reroutOutput(std::wofstream file);

private:
	static bool hasInit;

};

