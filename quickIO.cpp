#include "quickIO.h"
#include "stringTools.h"
#include "quickDir.h"

char* const quickIO::LINE_BREAK = new char[2]{ (char)13, (char)10 };
char const quickIO::READ = 0;
char const quickIO::WRITE = 1;
char const quickIO::WRITE_APPEND = 2;

quickIO::quickIO(wchar_t* filename, char type)
{
	this->type = type;
	this->size = 0;

	switch (type)
	{
	case quickIO::READ:
		//
		this->file = new fstream(filename, fstream::in | fstream::ate | fstream::binary);
		size = file->tellg();
		file->close();

		this->file = new fstream(filename, fstream::in | fstream::binary);

		this->wideFileName = filename;
		break;
	case quickIO::WRITE:
		//
		this->file = new fstream(filename, fstream::out | fstream::binary);
		this->wideFileName = filename;
		break;
	case quickIO::WRITE_APPEND:
		//
		this->file = new fstream(filename, fstream::in | fstream::ate | fstream::binary);
		size = file->tellg();
		file->close();

		this->file = new fstream(filename, fstream::out | fstream::app | fstream::binary);
		this->wideFileName = filename;
		break;
	default:
		this->file = new fstream(filename, fstream::in | fstream::ate | fstream::binary);
		size = file->tellg();
		file->close();

		this->file = new fstream(filename, fstream::in | fstream::binary);
		this->wideFileName = filename;
		break;
	}

}

quickIO::quickIO(char* filename, char type)
{
	this->type = type;
	this->size = 0;

	switch (type)
	{
	case quickIO::READ:
		//
		this->file = new fstream(filename, fstream::in | fstream::ate | fstream::binary);
		size = file->tellg();
		file->close();

		this->file = new fstream(filename, fstream::in | fstream::binary);

		this->wideFileName = (wchar_t*)filename;
		break;
	case quickIO::WRITE:
		//
		this->file = new fstream(filename, fstream::out | fstream::binary);
		this->wideFileName = (wchar_t*)filename;
		break;
	case quickIO::WRITE_APPEND:
		//
		this->file = new fstream(filename, fstream::in | fstream::ate | fstream::binary);
		size = file->tellg();
		file->close();

		this->file = new fstream(filename, fstream::out | fstream::app | fstream::binary);
		this->wideFileName = (wchar_t*)filename;
		break;
	default:
		this->file = new fstream(filename, fstream::in | fstream::ate | fstream::binary);
		size = file->tellg();
		file->close();

		this->file = new fstream(filename, fstream::in | fstream::binary);
		this->wideFileName = (wchar_t*)filename;
		break;
	}

}

quickIO::~quickIO()
{
}

int quickIO::readInt()
{
	if (isOpen() && type == quickIO::READ && !isEndOfFile())
	{
		return file->get();
	}
	else
	{
		stringTools::out << (int)isOpen() << stringTools::lineBreak;
		stringTools::out << (int)type << stringTools::lineBreak;
		stringTools::out << (int)isEndOfFile() << stringTools::lineBreak;

		stringTools::out << "Is not opened for reading" << stringTools::lineBreak;
	}
	return 0;
}

char quickIO::readByte()
{
	if (isOpen() && type == quickIO::READ && !isEndOfFile())
	{
		return file->get();
	}
	else
	{
		stringTools::out << "Is not opened for reading" << stringTools::lineBreak;
	}
	return '\0';
}

wchar_t toWideChar(unsigned char p, unsigned char p2)
{
	wchar_t n;

	n = p;
	n = n << 8;
	n += p2;

	return n;
}

wchar_t quickIO::readWideChar()
{
	unsigned char p1;
	unsigned char p2;
	wchar_t n;
	if (isOpen() && type == quickIO::READ && !isEndOfFile())
	{
		p2 = file->get();
		p1 = file->get();

		return toWideChar(p1, p2);
	}
	return L'\0';
}

const char * quickIO::readLine()
{
	string p = "";
	char c = '\0';

	if (isOpen() && type == quickIO::READ && !isEndOfFile())
	{
		while (!isEndOfFile())
		{
			c = file->get();

			if (c != LINE_BREAK[0])
			{
				p += c;
			}
			else
			{
				if (!isEndOfFile())
				{
					c = file->get();
					if (c == LINE_BREAK[1])
					{
						//Hit a line break
						break;
					}
					else
					{
						//Hit something else.
						//Fix later I guess.
						p += 13;
						p += c;
					}
				}
				else
				{
					p += c;
				}
			}
		}

		return p.c_str();
	}
	else
	{
		stringTools::out << "Is not opened for reading" << stringTools::lineBreak;
	}

	return nullptr;
}

const wchar_t * quickIO::readWideLine()
{
	wstring p = L"";
	wchar_t c = L'\0';
	unsigned char p1;
	unsigned char p2;
	wchar_t n;

	if (isOpen() && type == quickIO::READ && !isEndOfFile())
	{
		while (!isEndOfFile())
		{
			p2 = file->get();
			p1 = file->get();
			c = toWideChar(p1, p2);

			if (c != LINE_BREAK[0])
			{
				p += c;
			}
			else
			{
				if (!isEndOfFile())
				{
					p2 = file->get();
					p1 = file->get();
					n = toWideChar(p1, p2);

					if (n == LINE_BREAK[1])
					{
						//Hit a line break
						break;
					}
					else
					{
						//Hit something else.
						//Fix later I guess.
						p += c;
						p += n;
					}
				}
				else
				{
					p += c;
				}
			}
		}

		return p.c_str();
	}
	else
	{
		stringTools::out << "Is not opened for reading" << stringTools::lineBreak;
	}

	return nullptr;
}

string quickIO::readString()
{
	string p = "";
	char c = '\0';

	if (isOpen() && type == quickIO::READ && !isEndOfFile())
	{
		while (!isEndOfFile())
		{
			c = file->get();

			if (c != LINE_BREAK[0])
			{
				p += c;
			}
			else
			{
				if (!isEndOfFile())
				{
					c = file->get();
					if (c == LINE_BREAK[1])
					{
						//Hit a line break
						break;
					}
					else
					{
						//Hit something else.
						//Fix later I guess.
						p += 13;
						p += c;
					}
				}
				else
				{
					p += c;
				}
			}
		}
	}
	else
	{
		stringTools::out << "Is not opened for reading" << stringTools::lineBreak;
	}

	return p;
}

wstring quickIO::readWideString()
{
	wstring p = L"";
	wchar_t c = L'\0';
	unsigned char p1;
	unsigned char p2;
	wchar_t n;

	if (isOpen() && type == quickIO::READ && !isEndOfFile())
	{
		while (!isEndOfFile())
		{
			p2 = file->get();
			p1 = file->get();
			c = toWideChar(p1, p2);

			if (c != LINE_BREAK[0])
			{
				p += c;
			}
			else
			{
				if (!isEndOfFile())
				{
					p2 = file->get();
					p1 = file->get();
					n = toWideChar(p1, p2);

					if (n == LINE_BREAK[1])
					{
						//Hit a line break
						break;
					}
					else
					{
						//Hit something else.
						//Fix later I guess.
						p += c;
						p += n;
					}
				}
				else
				{
					p += c;
				}
			}
		}

	}
	else
	{
		stringTools::out << "Is not opened for reading" << stringTools::lineBreak;
	}

	return p;
}

vector<const char*> quickIO::readFullFile()
{
	vector<const char*> info = vector<const char*>();

	while (!isEndOfFile())
	{
		info.push_back(readLine());
	}

	return info;
}

vector<const wchar_t*> quickIO::readFullFileWide()
{
	//Read the first two bytes to determine if the file is a unicode file
	vector<const wchar_t*> info = vector<const wchar_t*>();

	char c1 = file->get();
	char c2 = file->get();

	if (c1 == 0xFF && c2 == 0xFE)
	{
		//Is unicode, proceed to read
		while (!isEndOfFile())
		{
			//read
			info.push_back(readWideLine());
		}
	}

	return vector<const wchar_t*>();
}

vector<string> quickIO::readFullFileString()
{
	vector<string> info = vector<string>();

	while (!isEndOfFile())
	{
		info.push_back(readString());
	}

	return info;
}

vector<wstring> quickIO::readFullFileStringWide()
{
	//Read the first two bytes to determine if the file is a unicode file
	vector<wstring> info = vector<wstring>();

	char c1 = file->get();
	char c2 = file->get();

	if (c1 == 0xFF && c2 == 0xFE)
	{
		//Is unicode, proceed to read
		while (!isEndOfFile())
		{
			//read
			info.push_back(readWideString());
		}
	}

	return info;
}

vector<char> quickIO::readFullFileAsBytes()
{
	vector<char> info = vector<char>();

	while (!isEndOfFile())
	{
		info.push_back(readByte());
	}

	return info;
}

void quickIO::writeByte(char c)
{
	if (isOpen())
	{
		if (type == WRITE || type == WRITE_APPEND)
		{
			file->put(c);
		}
		else
		{
			stringTools::out << "Is not opened for writing" << stringTools::lineBreak;
		}
	}
	else
	{
		stringTools::out << "File is not opened" << stringTools::lineBreak;
	}
}

void quickIO::writeWideChar(wchar_t c)
{
	if (isOpen())
	{
		if (type == WRITE || type == WRITE_APPEND)
		{
			file->put(c);
		}
		else
		{
			stringTools::out << "Is not opened for writing" << stringTools::lineBreak;
		}
	}
	else
	{
		stringTools::out << "File is not opened" << stringTools::lineBreak;
	}
}

void quickIO::writeLine(char * line)
{
	if (isOpen())
	{
		if (type == WRITE || type == WRITE_APPEND)
		{
			for (int i = 0; i < strlen(line); i++)
			{
				file->put(line[i]);
			}
		}
		else
		{
			stringTools::out << "Is not opened for writing" << stringTools::lineBreak;
		}
	}
	else
	{
		stringTools::out << "File is not opened" << stringTools::lineBreak;
	}
}

void quickIO::writeWideLine(wchar_t * line)
{
	if (isOpen())
	{
		if (type == WRITE || type == WRITE_APPEND)
		{
			for (int i = 0; i < wcslen(line); i++)
			{
				file->put(line[i]);
			}
		}
		else
		{
			stringTools::out << "Is not opened for writing" << stringTools::lineBreak;
		}
	}
	else
	{
		stringTools::out << "File is not opened" << stringTools::lineBreak;
	}
}

void quickIO::writeString(string line)
{
	if (isOpen())
	{
		if (type == WRITE || type == WRITE_APPEND)
		{
			for (int i = 0; i < line.size(); i++)
			{
				file->put(line[i]);
			}
		}
		else
		{
			stringTools::out << "Is not opened for writing" << stringTools::lineBreak;
		}
	}
	else
	{
		stringTools::out << "File is not opened" << stringTools::lineBreak;
	}
}

void quickIO::writeWideString(wstring line)
{
	if (isOpen())
	{
		if (type == WRITE || type == WRITE_APPEND)
		{
			for (int i = 0; i < line.size(); i++)
			{
				file->put(line[i]);
			}
		}
		else
		{
			stringTools::out << "Is not opened for writing" << stringTools::lineBreak;
		}
	}
	else
	{
		stringTools::out << "File is not opened" << stringTools::lineBreak;
	}
}

void quickIO::writeLineBreak()
{
	if (isOpen())
	{
		if (type == WRITE || type == WRITE_APPEND)
		{
			file->put(LINE_BREAK[0]);
			file->put(LINE_BREAK[1]);
		}
		else
		{
			stringTools::out << "Is not opened for writing" << stringTools::lineBreak;
		}
	}
	else
	{
		stringTools::out << "File is not opened" << stringTools::lineBreak;
	}
}

bool quickIO::isOpen()
{
	return file->is_open();
}

void quickIO::close()
{
	file->close();
}

bool quickIO::isEndOfFile()
{
	return file->eof();
}

wchar_t * quickIO::getFileName()
{
	return this->wideFileName;
}

wstring quickIO::getFileNameString()
{
	return wstring(wideFileName);
}

int quickIO::getSize()
{
	return size;
}

int quickIO::getBytesLeft()
{
	return size - file->tellg();
}
