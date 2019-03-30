#pragma once

#include<string>
#include<vector>
#include<fstream>
#include<iostream>

using namespace std;

class quickIO
{
public:
	static char const READ;
	static char const WRITE;
	static char const WRITE_APPEND;

	static char* const LINE_BREAK;

	quickIO(wchar_t* filename, const char type);
	quickIO(char* filename, const char type);

	~quickIO();

	//Read functions
	char readByte();
	int readInt();
	wchar_t readWideChar(); //Unicode capable
	const char* readLine();
	const wchar_t* readWideLine();
	string readString();
	wstring readWideString();

	vector<const char*> readFullFile();
	vector<const wchar_t*> readFullFileWide();

	vector<string> readFullFileString();
	vector<wstring> readFullFileStringWide();
	
	vector<char> readFullFileAsBytes();

	//Write functions
	void writeByte(char c);
	void writeWideChar(wchar_t c); //Unicode capable
	void writeLine(char* line);
	void writeWideLine(wchar_t* line); //Unicode capable

	void writeString(string line);
	void writeWideString(wstring line); //Unicode capable

	void writeLineBreak();

	//File functions
	bool isOpen();
	void close();
	bool isEndOfFile();
	wchar_t* getFileName();
	wstring getFileNameString();

	int getSize();
	int getBytesLeft();

private:
	wchar_t* wideFileName; //Unicode capable
	char type;
	fstream* file;
	int size;
	
};

