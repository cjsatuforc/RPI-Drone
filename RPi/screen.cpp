#include "mailbox-interface.h"
#include "screen.h"
#include "font.h"
#include "systimer.h"
#include "gpio.h"

#include "definitions.h"
#include <cstring>
#include <stdio.h>
#include "string.h"

rpi_screen_t rpiScreen;
unsigned int gCursorX = 0;
unsigned int gCursorY = 0;

rpi_screen_t* RPI_GetScreen()
{
	return &rpiScreen;
}

color32_t rpi_screen_t::getPixel(unsigned int x, unsigned int y)
{
	if (x >= mWidth || y >= mHeight)
		return 0;
	if (mDepth == 32)
		return ((color32_t*)pData)[x + (mWidth * y)];
	else if (mDepth == 24)
		return (color32_t)((color24_t*)pData)[x + (mWidth * y)];
	else if (mDepth == 16)
		return (color32_t)((color16_t*)pData)[x + (mWidth * y)];
	else if (mDepth == 8)
		return (color32_t)((color8_t*)pData)[x + (mWidth * y)];
	return 0;
}

void rpi_screen_t::setPixel(unsigned int x, unsigned int y, color32_t color)
{
	if (x >= mWidth || y >= mHeight)
		return;
	if (mDepth == 32)
		((color32_t*)pData)[x + (mWidth * y)] = color;
	else if (mDepth == 24)
		((color24_t*)pData)[x + (mWidth * y)] = color;
	else if (mDepth == 16)
		((color16_t*)pData)[x + (mWidth * y)] = color;
	else if (mDepth == 8)
		((color8_t*)pData)[x + (mWidth * y)] = color;
}

void rpi_screen_t::init(int& w, int& h, int& bpp, int& pitch)
{
	RPI_PropertyInit();
	RPI_PropertyAddTag(TAG_ALLOCATE_BUFFER);
	RPI_PropertyAddTag(TAG_SET_PHYSICAL_SIZE, w, h);
	RPI_PropertyAddTag(TAG_SET_VIRTUAL_SIZE, w, h);
	RPI_PropertyAddTag(TAG_SET_DEPTH, bpp);
	RPI_PropertyAddTag(TAG_GET_PITCH);
	RPI_PropertyAddTag(TAG_GET_PHYSICAL_SIZE);
	RPI_PropertyAddTag(TAG_GET_DEPTH);
	RPI_PropertyProcess();

	rpi_mailbox_property_t* mp;

	if ((mp = RPI_PropertyGet(TAG_GET_PHYSICAL_SIZE)))
	{
		mWidth = w = mp->data.buffer_32[0];
		mHeight = h = mp->data.buffer_32[1];
	}

	if ((mp = RPI_PropertyGet(TAG_GET_DEPTH)))
	{
		mDepth = bpp = mp->data.buffer_32[0];
		switch (mDepth)
		{
		default:
		case 32:
			//clear_func = [&](unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
			//	clear_int(r, g, b, a);
			//};
			break;
		case 24:
			
			break;
		case 16:
			//clear_func = [&](unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
			//	clear_short(r, g, b, a);
			//};
			break;
		case 8:
			//clear_func = [&](unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
			//	clear_byte(r, g, b, a);
			//};
			break;
		}
	}

	if ((mp = RPI_PropertyGet(TAG_GET_PITCH)))
	{
		mPitch = pitch = mp->data.buffer_32[0];
	}

	if ((mp = RPI_PropertyGet(TAG_ALLOCATE_BUFFER)))
	{
		pData = (void*)mp->data.buffer_32[0];
	}
}

void rpi_screen_t::setBackgroundColor(color32_t c)
{
	//mBackgroundColor = (int)c;
}

void rpi_screen_t::setForegroundColor(color32_t c)
{
	//mForegroundColor = (int)c;
}

void rpi_screen_t::clear()
{
	color32_t mBackgroundColor = 0;
	if (mDepth == 32)
		clear32((color32_t)mBackgroundColor);
	else if (mDepth == 24)
		clear24((color32_t)mBackgroundColor);
	else if (mDepth == 16)
		clear16((color32_t)mBackgroundColor);
	else if (mDepth == 8)
		clear8((color32_t)mBackgroundColor);
	gCursorX = 0;
	gCursorY = 0;
};

void rpi_screen_t::drawText(unsigned int x, unsigned int y, char const* text)
{
	unsigned int cX = gCursorX;
	unsigned int cY = gCursorY;

	gCursorX = x;
	gCursorY = y;

	size_t len = strlen(text);
	for (size_t i = 0; i < len; ++i)
		outbyte(text[i], x);

	gCursorX = cX;
	gCursorY = cY;
}

void rpi_screen_t::outbyte(char b, unsigned int xReset)
{
	if (b == '\n')
	{
		gCursorY += 16;
		gCursorX = xReset;
		return;
	}

	if (gCursorX + 8 >= mWidth)
	{
		gCursorY += 16;
		gCursorX = xReset;
	}

	unsigned char* cData = RPI_GetFontCharacter(b);
	for (unsigned int j = 0; j < 12; ++j)
		for (unsigned int i = 0; i < 8; ++i)
		{
			setPixel(gCursorX + i, gCursorY + j, ((cData[j] & (1 << (8 - i))) != 0) ? -1 : 0);
		}
	gCursorX += 8;
}

void rpi_screen_t::clear32(color32_t c)
{
	memset32(pData, (int)c, mWidth * mHeight);
}

void rpi_screen_t::clear24(color24_t c)
{
	memset(pData, (int)c, mWidth * mHeight * 3);
}

void rpi_screen_t::clear16(color16_t c)
{
	memset(pData, (short)c, mWidth * mHeight * 2);
}

void rpi_screen_t::clear8(color8_t c)
{
	memset(pData, (unsigned char)c, mWidth * mHeight);
}

void rpi_screen_t::drawInfo()
{
	//char message[256];
	//snprintf(message, 256, "Width: %i\n" \
	//	"Height: %i\n" \
	//	"Depth: %i\n" \
	//	"Pitch: %i\n",
	//	mWidth,
	//	mHeight,
	//	mDepth,
	////	mPitch);
	//drawText(0, 0, message);
}
