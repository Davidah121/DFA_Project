#include "stringTools.h"

std::wostream stringTools::out(nullptr);
std::wistream stringTools::in(nullptr);
std::wostream stringTools::err(nullptr);

bool stringTools::hasInit = false;

wchar_t const stringTools::lineBreak = '\n';


stringTools::stringTools()
{
	
}


stringTools::~stringTools()
{
}

void stringTools::init()
{
	std::ios_base::sync_with_stdio(false);
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);
	_setmode(_fileno(stderr), _O_U16TEXT);

	stringTools::out.rdbuf(std::wcout.rdbuf());
	stringTools::in.rdbuf(std::wcin.rdbuf());
	stringTools::err.rdbuf(std::wcerr.rdbuf());

}

wchar_t * stringTools::toWideString(char * text)
{
	wchar_t* temp = new wchar_t[ stringLength(text) ];
	for (int i = 0; i <= stringLength(text); i++)
	{
		temp[i] = (wchar_t)text[i];
	}
	return temp;
}

wchar_t * stringTools::toWideString(const char * text)
{
	wchar_t* temp = new wchar_t[stringLength(text)];
	for (int i = 0; i <= stringLength(text); i++)
	{
		temp[i] = (wchar_t)text[i];
	}
	return temp;
}

char * stringTools::toCString(wchar_t * text)
{
	char* temp = new char[stringLength(text)];
	for (int i = 0; i <= stringLength(text); i++)
	{
		temp[i] = text[i] & 0xFF;
	}
	return temp;
}

char * stringTools::toCString(const wchar_t * text)
{
	char* temp = new char[stringLength(text)];
	for (int i = 0; i <= stringLength(text); i++)
	{
		temp[i] = text[i] & 0xFF;
	}
	return temp;
}

int stringTools::stringLength(char * text)
{
	return std::strlen(text);
}

int stringTools::stringLength(const char * text)
{
	return std::strlen(text);
}

int stringTools::stringLength(wchar_t * text)
{
	return std::wcslen(text);
}

int stringTools::stringLength(const wchar_t * text)
{
	return std::wcslen(text);
}

char valueToHex(char val)
{
	switch (val)
	{
	default:
		return (char)(48 + val);
		break;
	case 10:
		return 'A';
		break;
	case 11:
		return 'B';
		break;
	case 12:
		return 'C';
		break;
	case 13:
		return 'D';
		break;
	case 14:
		return 'E';
		break;
	case 15:
		return 'F';
		break;
	}
}

char* stringTools::pointerToString(void * location)
{
	return toHexString((int)location);
}

char* stringTools::toHexString(char value)
{
	char* hexString = new char[3];

	unsigned char firstValue = (value >> 4)&0xF; // High bits
	unsigned char secondValue = (value)&0xF; // Low bits

	hexString[0] = valueToHex(firstValue);
	hexString[1] = valueToHex(secondValue);
	hexString[2] = '\0';

	return hexString;
}

char* stringTools::toHexString(short value)
{
	char* hexString = new char[5];

	hexString[0] = valueToHex((value >> 12) & 0xF);
	hexString[1] = valueToHex((value >> 8) & 0xF);
	hexString[2] = valueToHex((value >> 4) & 0xF);
	hexString[3] = valueToHex((value) & 0xF);
	hexString[4] = '\0';

	return hexString;
}

char* stringTools::toHexString(int value)
{
	char* hexString = new char[9];

	hexString[0] = valueToHex((value >> 28) & 0xF);
	hexString[1] = valueToHex((value >> 24) & 0xF);
	hexString[2] = valueToHex((value >> 20) & 0xF);
	hexString[3] = valueToHex((value >> 16) & 0xF);
	hexString[4] = valueToHex((value >> 12) & 0xF);
	hexString[5] = valueToHex((value >> 8) & 0xF);
	hexString[6] = valueToHex((value >> 4) & 0xF);
	hexString[7] = valueToHex((value) & 0xF);
	hexString[8] = '\0';

	return hexString;
}

char* stringTools::toHexString(long value)
{
	char* hexString = new char[17];

	hexString[0] = valueToHex((value >> 60) & 0xF);
	hexString[1] = valueToHex((value >> 56) & 0xF);
	hexString[2] = valueToHex((value >> 52) & 0xF);
	hexString[3] = valueToHex((value >> 48) & 0xF);
	hexString[4] = valueToHex((value >> 44) & 0xF);
	hexString[5] = valueToHex((value >> 40) & 0xF);
	hexString[6] = valueToHex((value >> 36) & 0xF);
	hexString[7] = valueToHex((value >> 32) & 0xF);
	hexString[8] = valueToHex((value >> 28) & 0xF);
	hexString[9] = valueToHex((value >> 24) & 0xF);
	hexString[10] = valueToHex((value >> 20) & 0xF);
	hexString[11] = valueToHex((value >> 16) & 0xF);
	hexString[12] = valueToHex((value >> 12) & 0xF);
	hexString[13] = valueToHex((value >> 8) & 0xF);
	hexString[14] = valueToHex((value >> 4) & 0xF);
	hexString[15] = valueToHex((value) & 0xF);
	hexString[16] = '\0';

	return hexString;
}

std::wstring stringTools::getWideString()
{
	std::wstring temp = L"";

	std::getline(in, temp);

	return temp;
}

std::string stringTools::getString()
{
	std::wstring temp = L"";
	
	std::getline(in, temp);
	
	std::string text = (char*)temp.c_str();

	return text;
}

char stringTools::getChar()
{
	std::wstring temp = L"";
	std::getline(in, temp);
	
	return (char)temp.at(0);
}

wchar_t stringTools::getWideChar()
{
	std::wstring temp = L"";
	std::getline(in, temp);

	return temp.at(0);
}

int stringTools::getInt()
{
	return std::cin.get();
}

std::vector<std::string> stringTools::splitString(std::string s, char delim)
{
	std::vector<std::string> stringArray = std::vector<std::string>();

	std::string temp = "";

	int i = 0;
	while (i < s.size())
	{
		if (s.at(i) != delim)
		{
			temp += s.at(i);
		}
		else
		{
			stringArray.push_back(temp);
			temp = "";
		}
		i++;
	}

	stringArray.push_back(temp);

	return stringArray;
}

std::vector<std::string> stringTools::splitString(std::string s, char * delim)
{
	std::vector<std::string> stringArray = std::vector<std::string>();

	std::string temp = "";
	std::string otherString = "";

	int dSize = std::strlen(delim);

	int i = 0;
	int count = 0;

	while (i < s.size())
	{
		if (s.at(i) != delim[0])
		{
			temp += s.at(i);
			i++;
		}
		else
		{
			if (dSize + i <= s.size())
			{
				//possible that it could still contain
				//the substring

			}
			while (count < dSize)
			{
				if (s.at(i + count) = delim[count])
				{
					otherString += delim[count];
				}
				else
				{
					break;
				}
				count++;
			}

			if (count == dSize)
			{
				//Found subString
				stringArray.push_back(temp);
				temp = "";
				i += count;

				count = 0;
				otherString = "";
			}
			else
			{
				temp += otherString;
			}
			
		}
	}

	stringArray.push_back(temp);

	return stringArray;
}

int stringTools::toInt(std::string s)
{
	return std::stoi(s.c_str());
}

long stringTools::toLong(std::string s)
{
	return std::stol(s.c_str());
}

double stringTools::toDouble(std::string s)
{
	return std::stod(s.c_str());
}

float stringTools::toFloat(std::string s)
{
	return std::stof(s.c_str());
}

void stringTools::print(char text)
{
	stringTools::out << text;
}

void stringTools::println(char text)
{
	stringTools::out << text << stringTools::lineBreak;
}

void stringTools::print(wchar_t text)
{
	stringTools::out << text;
}

void stringTools::println(wchar_t text)
{
	stringTools::out << text << stringTools::lineBreak;
}

void stringTools::print(char * text)
{
	stringTools::out << text;
}

void stringTools::println(char * text)
{
	stringTools::out << text << stringTools::lineBreak;
}

void stringTools::print(wchar_t * text)
{
	stringTools::out << text;
}

void stringTools::println(wchar_t * text)
{
	stringTools::out << text << stringTools::lineBreak;
}

void stringTools::print(std::string text)
{
	stringTools::out << text.c_str();
}

void stringTools::println(std::string text)
{
	stringTools::out << text.c_str() << stringTools::lineBreak;
}

void stringTools::print(std::wstring text)
{
	stringTools::out << text.c_str();
}

void stringTools::println(std::wstring text)
{
	stringTools::out << text.c_str() << stringTools::lineBreak;
}

void stringTools::print(int text)
{
	stringTools::out << text;
}

void stringTools::println(int text)
{
	stringTools::out << text << stringTools::lineBreak;
}

void stringTools::print(double text)
{
	stringTools::out << text;
}

void stringTools::println(double text)
{
	stringTools::out << text << stringTools::lineBreak;
}

void stringTools::print(float text)
{
	stringTools::out << text;
}

void stringTools::println(float text)
{
	stringTools::out << text << stringTools::lineBreak;
}

void stringTools::print(long text)
{
	stringTools::out << text;
}

void stringTools::println(long text)
{
	stringTools::out << text << stringTools::lineBreak;
}

void stringTools::print(void* text)
{
	stringTools::out << text;
}

void stringTools::println(void* text)
{
	stringTools::out << text << stringTools::lineBreak;
}