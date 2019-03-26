#include "Renderer.h"
#include <iostream>
#include "MathExt.h"

Bitmap* Renderer::bindedImage = nullptr;
Color Renderer::drawColor = { 255,0,0 };

Renderer::Renderer()
{
}


Renderer::~Renderer()
{
}

void Renderer::bindImage(Bitmap * img)
{
	bindedImage = img;
}

void Renderer::clear()
{
	if (bindedImage != nullptr)
	{
		int size = bindedImage->getWidth() * bindedImage->getHeight();
		
		
		Color* pixValues = bindedImage->getPixels();
		Color* pixValuesEnd = bindedImage->getPixels() + size;

		while (pixValues < pixValuesEnd)
		{
			*pixValues = drawColor;
			pixValues++;
		}
	}
}

void Renderer::drawRect(int x, int y, int width, int height)
{
	if (bindedImage != nullptr)
	{
		int swap = 0;

		int x1 = MathExt::clamp(x, 0, bindedImage->getWidth());
		int x2 = MathExt::clamp(x+width, 0, bindedImage->getWidth());

		int y1 = MathExt::clamp(y, 0, bindedImage->getHeight());
		int y2 = MathExt::clamp(y+height, 0, bindedImage->getHeight());

		if (x1 > x2)
		{
			swap = x2;
			x2 = x1;
			x1 = swap;
		}

		if (y1 > y2)
		{
			swap = y2;
			y2 = y1;
			y1 = swap;
		}

		if (x1 < bindedImage->getWidth() && y1 < bindedImage->getHeight())
		{
			int size = bindedImage->getWidth() * bindedImage->getHeight();
			Color* pixValuesStart = bindedImage->getPixels() + x1 + (y1*bindedImage->getWidth());

			int i = 0;
			int addAmount = bindedImage->getWidth() - (x2 - x1) + 1;

			Color* pixValuesEnd = bindedImage->getPixels() + x2 + (y2*bindedImage->getWidth());

			while (pixValuesStart < pixValuesEnd)
			{
				*pixValuesStart = drawColor;
				i++;

				if (i >= (x2 - x1))
				{
					pixValuesStart += addAmount;
					i = 0;
				}
				else
				{
					pixValuesStart++;
				}
			}
		}
	}
}
void Renderer::drawImage(Bitmap* img, int x, int y)
{
	if (bindedImage != nullptr)
	{
		int x1 = MathExt::clamp(x, 0, bindedImage->getWidth());
		int x2 = MathExt::clamp(x + img->getWidth(), 0, bindedImage->getWidth());

		int y1 = MathExt::clamp(y, 0, bindedImage->getHeight());
		int y2 = MathExt::clamp(y + img->getHeight(), 0, bindedImage->getHeight());

		if (x1 < bindedImage->getWidth() && y1 < bindedImage->getHeight())
		{
			Color* sourceStart = img->getPixels();
			Color* sourceEnd = img->getPixels()+(img->getWidth()*img->getHeight());

			Color* destStart = bindedImage->getPixels() + x1 + (y1*bindedImage->getWidth());

			int i = 0;

			int addAmountDest = bindedImage->getWidth() - (x2 - x1) + 1;
			int addAmountSource = img->getWidth() - (x2 - x1) + 1;

			Color* destEnd = bindedImage->getPixels() + x2 + (y2*bindedImage->getWidth());

			while (destStart < destEnd && sourceStart < sourceEnd)
			{
				*destStart = *sourceStart;
				i++;

				if (i >= (x2 - x1))
				{
					destStart += addAmountDest;
					sourceStart += addAmountSource;
					i = 0;
				}
				else
				{
					destStart++;
					sourceStart++;
				}
			}
		}
	}
}
void Renderer::setDrawColor(Color v)
{
	drawColor = v;
}
