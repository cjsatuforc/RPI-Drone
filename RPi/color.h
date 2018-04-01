#pragma once

struct color24_t;
struct color16_t;
struct color8_t;

typedef struct color32_t {

	color32_t();
	color32_t(unsigned int i);
	color32_t(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255);
	color32_t(color24_t c, unsigned char a = 255);
	color32_t(color16_t c, unsigned char a = 255);
	color32_t(color8_t c);

	inline void a(unsigned char a) { mA = a; }
	inline void r(unsigned char r) { mR = r; }
	inline void g(unsigned char g) { mG = g; }
	inline void b(unsigned char b) { mB = b; }
	
	inline unsigned char a() { return mA; }
	inline unsigned char r() { return mR; }
	inline unsigned char g() { return mG; }
	inline unsigned char b() { return mB; }

	//0 for r, 1 for g, 2 for b, 3 for a
	inline unsigned char operator[](unsigned int i) {
		return (i < 4) ? (((unsigned char*)this)[(i + 1) % 4]) : 0;
	}

	inline explicit operator int()
	{
		return (mA << 24) | (mR << 16) | (mG << 8) | mB;
	}

private:
	unsigned char mA;
	unsigned char mR;
	unsigned char mG;
	unsigned char mB;
} color32_t;

typedef struct color24_t {

	color24_t();
	color24_t(color32_t c);
	color24_t(color16_t c);
	color24_t(color8_t c);

	inline void r(unsigned char r) { mR = r; }
	inline void g(unsigned char g) { mG = g; }
	inline void b(unsigned char b) { mB = b; }

	inline unsigned char r() { return mR; }
	inline unsigned char g() { return mG; }
	inline unsigned char b() { return mB; }

	//0 for r, 1 for g, 2 for b
	inline unsigned char operator[](unsigned int i) {
		return (i < 3) ? (((unsigned char*)this)[i]) : 0;
	}

	inline explicit operator int()
	{
		return (mR << 16) | (mG << 8) | mB;
	}

private:
	unsigned char mR;
	unsigned char mG;
	unsigned char mB;
} color24_t;

typedef struct color16_t {

	color16_t();
	color16_t(color32_t c);
	color16_t(color24_t c);
	color16_t(color8_t color);

	inline void r(unsigned char r) { c &= 0b0000011111111111; c |= (r >> 3) << 11; }
	inline void g(unsigned char g) { c &= 0b1111100000011111; c |= (g >> 2) << 5; }
	inline void b(unsigned char b) { c &= 0b1111111111100000; c |= (b >> 3); }

	inline unsigned char r() { return (unsigned char)(((c >> 11) & 0b11111) << 3); }
	inline unsigned char g() { return (unsigned char)(((c >> 5) & 0b111111) << 2); }
	inline unsigned char b() { return (unsigned char)(((c & 0b11111) << 3)); }

	inline explicit operator short()
	{
		return c;
	}

private:
	unsigned short c;
} color16_t;

typedef struct color8_t {

	color8_t(color32_t c);
	color8_t(color24_t c);
	color8_t(color16_t c);

	void index(unsigned char i) { mIndex = i; }
	unsigned char index() { return mIndex; }

	inline explicit operator unsigned char()
	{
		return mIndex;
	}

private:
	unsigned char mIndex;
} color8_t;