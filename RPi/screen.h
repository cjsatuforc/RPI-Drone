#pragma once

#include "color.h"

typedef struct rpi_screen_t
{
	color32_t getPixel(unsigned int x, unsigned int y);
	void setPixel(unsigned int x, unsigned int y, color32_t color);
	void init(int& width, int& height, int& bpp, int& pitch);
	void setBackgroundColor(color32_t);
	void setForegroundColor(color32_t);
	void clear();
	void drawText(unsigned int x, unsigned int y, char const* text);
	void outbyte(char b, unsigned int xResetPos);
	void drawInfo();

protected:
	void clear32(color32_t);
	void clear24(color24_t);
	void clear16(color16_t);
	void clear8(color8_t);

	void* pData;
	unsigned int mWidth;
	unsigned int mHeight;
	unsigned int mDepth;
	unsigned int mPitch;
	//color32_t mBackgroundColor;
	//color32_t mForegroundColor;
} rpi_screen_t;

extern rpi_screen_t* RPI_GetScreen();