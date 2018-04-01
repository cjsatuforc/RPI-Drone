#include "color.h"
#include "string.h"

color32_t::color32_t() {
	mA = 255;
	mR = 0;
	mG = 0;
	mB = 0;
	//memset(&mR, 0, 3);
}

color32_t::color32_t(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a)
{
	r(_r);
	g(_g);
	b(_b);
	a(_a);
}

color32_t::color32_t(unsigned int i) {
	memcpy(this, &i, 4);
}

color32_t::color32_t(color24_t c, unsigned char a)
{
	mA = a;
	memcpy(&mR, &c, 3);
}

color32_t::color32_t(color16_t c, unsigned char a)
{
	mA = a;
	mR = c.r();
	mG = c.g();
	mB = c.b();
}

color32_t::color32_t(color8_t c)
{
	r(c.index());
}



color24_t::color24_t() {
	memset(this, 0, 3);
}

color24_t::color24_t(color32_t c) {
	r(c.r());
	g(c.g());
	b(c.b());
}

color24_t::color24_t(color16_t c)
{
	r(c.r());
	g(c.g());
	b(c.b());
}

color24_t::color24_t(color8_t c)
{
	r(c.index());
}



color16_t::color16_t()
{
	memset(this, 0, 2);
}

color16_t::color16_t(color32_t c)
{
	r(c.r());
	g(c.g());
	b(c.b());
}

color16_t::color16_t(color24_t c)
{
	r(c.r());
	g(c.g());
	b(c.b());
}

color16_t::color16_t(color8_t color)
{
	((unsigned char*)&c)[0] = color.index();
}



color8_t::color8_t(color32_t c)
{
	index(c.r());
}

color8_t::color8_t(color24_t c)
{
	index(c.r());
}

color8_t::color8_t(color16_t c)
{
	index(((unsigned char*)(&c))[0]);
}
