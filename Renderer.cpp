#include "Renderer.h"
#include <iostream>
#include "MathExt.h"

Bitmap* Renderer::bindedImage = nullptr;
Color Renderer::drawColor = { 255,0,0 };
BMPFont* Renderer::bindedFont = nullptr;

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

void Renderer::bindFont(BMPFont * font)
{
	bindedFont = font;
}

Bitmap * Renderer::getBindedImage()
{
	return bindedImage;
}

BMPFont * Renderer::getBindedFont()
{
	return bindedFont;
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

void Renderer::drawCircle(int x, int y, int radius)
{
	if (bindedImage != nullptr)
	{
		int x1 = MathExt::clamp(x - radius, 0, bindedImage->getWidth());
		int y1 = MathExt::clamp(y - radius, 0, bindedImage->getHeight());

		int x2 = MathExt::clamp(x + radius, 0, bindedImage->getWidth());
		int y2 = MathExt::clamp(y + radius, 0, bindedImage->getHeight());

		int swap;

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

			int ourX = -radius;
			int ourY = -radius;

			int radSqr = radius * radius;

			int addAmount = bindedImage->getWidth() - (x2 - x1) + 1;

			Color* pixValuesEnd = bindedImage->getPixels() + x2 + (y2*bindedImage->getWidth());

			while (pixValuesStart < pixValuesEnd)
			{
				if (ourX*ourX + ourY*ourY <= radSqr)
				{
					*pixValuesStart = drawColor;
				}

				i++;
				ourX++;
				if (i >= (x2 - x1))
				{
					pixValuesStart += addAmount;
					i = 0;
					ourX = -radius;
					ourY += 1;
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

			unsigned char* sourceAlphaStart = img->getAlphaChannel();
			unsigned char* sourceAlphaEnd = img->getAlphaChannel() + (img->getWidth()*img->getHeight());

			Color* destStart = bindedImage->getPixels() + x1 + (y1*bindedImage->getWidth());
			Color* destEnd = bindedImage->getPixels() + x2 + (y2*bindedImage->getWidth());

			unsigned char* destAlphaStart = bindedImage->getAlphaChannel() + x1 + (y1*bindedImage->getWidth());
			unsigned char* destAlphaEnd = bindedImage->getAlphaChannel() + x2 + (y2*bindedImage->getWidth());

			int i = 0;

			int addAmountDest = bindedImage->getWidth() - (x2 - x1) + 1;
			int addAmountSource = img->getWidth() - (x2 - x1) + 1;

			
			while (destStart < destEnd && sourceStart < sourceEnd)
			{
				if (*sourceAlphaStart != 0)
				{
					Color c = *sourceStart;
					c.b = (unsigned char)(c.b * (255.0 / drawColor.b));
					c.g = (unsigned char)(c.g * (255.0 / drawColor.g));
					c.r = (unsigned char)(c.r * (255.0 / drawColor.r));

					*destStart = c;
				}
				i++;

				if (i >= (x2 - x1))
				{
					destStart += addAmountDest;
					destAlphaStart += addAmountDest;
					sourceStart += addAmountSource;
					sourceAlphaStart += addAmountSource;
					i = 0;
				}
				else
				{
					destStart++;
					destAlphaStart++;
					sourceStart++;
					sourceAlphaStart++;
				}
			}
		}
	}
}

void Renderer::drawImagePart(Bitmap * img, int x, int y, int leftCull, int topCull, int rightCull, int bottomCull)
{
	if (leftCull >= 0 && rightCull >= 0 && topCull >= 0 && bottomCull >= 0)
	{
		if (bindedImage != nullptr)
		{
			//First separate the part of the image you want into a separate buffer
			int tempRightCull = MathExt::clamp(rightCull, 0, img->getWidth());
			int tempWidth = tempRightCull - leftCull;
			
			if (tempWidth <= 0)
			{
				//Not valid quit early
				return;
			}

			int tempBottomCull = MathExt::clamp(bottomCull, 0, img->getHeight());
			int tempHeight = tempBottomCull - topCull;

			if (tempHeight <= 0)
			{
				//Not valid quit early
				return;
			}

			int x1 = MathExt::clamp(x, 0, bindedImage->getWidth());
			int x2 = MathExt::clamp(x + tempWidth, 0, bindedImage->getWidth());

			int y1 = MathExt::clamp(y, 0, bindedImage->getHeight());
			int y2 = MathExt::clamp(y + tempHeight, 0, bindedImage->getHeight());

			if (x1 < bindedImage->getWidth() && y1 < bindedImage->getHeight())
			{
				Color* sourceStart = img->getPixels() + leftCull + (topCull*img->getWidth());
				Color* sourceEnd = img->getPixels() + tempRightCull + (tempBottomCull*img->getWidth());

				unsigned char* sourceAlphaStart = img->getAlphaChannel() + leftCull + (topCull*img->getWidth());
				unsigned char* sourceAlphaEnd = img->getAlphaChannel() + tempRightCull + (tempBottomCull*img->getWidth());


				Color* destStart = bindedImage->getPixels() + x1 + (y1*bindedImage->getWidth());
				Color* destEnd = bindedImage->getPixels() + x2 + (y2*bindedImage->getWidth());
				
				unsigned char* destAlphaStart = bindedImage->getAlphaChannel() + x1 + (y1*bindedImage->getWidth());
				unsigned char* destAlphaEnd = bindedImage->getAlphaChannel() + x2 + (y2*bindedImage->getWidth());


				int i = 0;

				int addAmountDest = bindedImage->getWidth() - (x2 - x1) + 1;
				int addAmountSource = img->getWidth() - (x2 - x1) + 1;
				
				while (destStart < destEnd && sourceStart < sourceEnd)
				{
					if (*sourceAlphaStart != 0)
					{
						Color c = *sourceStart;
						c.b = (unsigned char)(c.b * (255.0 / drawColor.b));
						c.g = (unsigned char)(c.g * (255.0 / drawColor.g));
						c.r = (unsigned char)(c.r * (255.0 / drawColor.r));

						*destStart = c;
					}
					i++;

					if (i >= (x2 - x1))
					{
						destStart += addAmountDest;
						destAlphaStart += addAmountDest;
						sourceStart += addAmountSource;
						sourceAlphaStart += addAmountSource;
						i = 0;
					}
					else
					{
						destStart++;
						destAlphaStart++;
						sourceStart++;
						sourceAlphaStart++;
					}
				}
			}
		}
	}
}

void Renderer::drawText(std::string s, int x, int y)
{
	if (bindedImage != nullptr && bindedFont != nullptr)
	{
		int xOff = 0;
		int yOff = 0;
		for (int i = 0; i < s.size(); i++)
		{
			Box b = bindedFont->getCharInfo(s.at(i));

			if (s.at(i) == '\n')
			{
				//Line break;
				xOff = 0;
				yOff += bindedFont->getFontSize();
			}
			else if(s.at(i)>=32)
			{
				drawImagePart(bindedFont->getFontImage(), x + xOff, y + yOff, b.x, b.y, b.x + b.width, b.y + b.height);
				xOff += b.width;
			}
		}
	}
}

void Renderer::setDrawColor(Color v)
{
	drawColor = v;
}
