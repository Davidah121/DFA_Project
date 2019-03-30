#include "BMPFont.h"
#include "quickIO.h"
#include "stringTools.h"

BMPFont::BMPFont(const char * filename)
{
	loadStuff(filename);
}

BMPFont::~BMPFont()
{
	fontInfo.clear();
}

Box BMPFont::getCharInfo(unsigned char c)
{
	int v = (int)c;

	if (v < fontInfo.size())
	{
		return fontInfo[v];
	}

	return Box();
}

Bitmap * BMPFont::getFontImage()
{
	return fontImage;
}

int BMPFont::getFontSize()
{
	return fontSize;
}

void BMPFont::loadStuff(const char * filename)
{
	std::string ftString = filename;
	ftString += ".ft";

	std::string currLine = "";

	quickIO file = quickIO((char*)ftString.c_str(), quickIO::READ);

	if (file.isOpen())
	{
		file.readString();
		file.readString();
		fontSize = stringTools::toInt(file.readString());
		file.readString();
		file.readString();

		while (!file.isEndOfFile())
		{
			currLine = file.readString();
			std::vector<std::string> splitString = stringTools::splitString(currLine, ',');

			if (splitString.size() == 5)
			{
				int cVal = stringTools::toInt(splitString[0]);
				int x = stringTools::toInt(splitString[1]);
				int y = stringTools::toInt(splitString[2]);
				int width = stringTools::toInt(splitString[3]);
				int height = stringTools::toInt(splitString[4]);

				Box b = Box(x, y, width, height);
				//Assume that the ft file already list the other chars before

				fontInfo.push_back(b);
			}
			else
			{
				//End of the file
				break;
			}
		}
	}
	else
	{
		//Not a valid name
	}
	
	std::string imageName = filename;
	imageName += ".bmp";

	fontImage = Bitmap::loadImage((char*)imageName.c_str());

	Color* pixels = fontImage->getPixels();
	unsigned char* alphaChannel = fontImage->getAlphaChannel();

	Color* endPixels = fontImage->getPixels() + fontImage->getWidth()*fontImage->getHeight();

	while (pixels < endPixels)
	{
		Color c = *pixels;

		if (c.r == 0 && c.g == 0 && c.b == 0)
		{
			*alphaChannel = 0;
		}
		alphaChannel++;
		pixels++;
	}

}
