#pragma once

#include "I2CSensorInterface.h"

class L3G4200D : public I2CSensorInterface
{
public:
	enum FullScale
	{
		FS250 = 0b00,
		FS500 = 0b01,
		FS2000 = 0b10
	};

	enum OutputDataRate
	{
		ODR100Hz = 0b00,
		ODR200Hz = 0b01,
		ODR400Hz = 0b10,
		ODR800Hz = 0b11
	};
	enum Bandwidth
	{
		BWLow = 0b00,
		BWMediumLow = 0b01,
		BWMediumHigh = 0b10,
		BWHigh = 0b11
	}; 
	L3G4200D();
	L3G4200D(const L3G4200D& other) = delete;
	L3G4200D(L3G4200D&& other) = delete;

	void SetOutputDataRate(OutputDataRate ODR);
	void SetBandwidth(Bandwidth BW);
	void SetFullScale(FullScale FS);
	void SetPower(bool val);
	void SetLPFEnabled(bool val);
	void SetHPFEnabled(bool val);

	void Calibrate();
	void Tick();

	bool HasNewData() const;
	bool HasOverrun() const;
	bool IsCalibrated() const;

	//Raw sensor measurements
	int16_t GetRawX() const;
	int16_t GetRawY() const;
	int16_t GetRawZ() const;

	//Last values in degrees per second
	float GetX() const;
	float GetY() const;
	float GetZ() const;

private:
	void UpdateLPFHPFConfig();

	int16_t mRawX;
	int16_t mRawY;
	int16_t mRawZ;

	int16_t mAvgX;
	int16_t mAvgY;
	int16_t mAvgZ;

	float mX;
	float mY;
	float mZ;

	bool mHasNewData;
	bool mHasOverrun;
	bool mIsCalibrated;
	bool mLPFEnabled;
	bool mHPFEnabled;

	OutputDataRate mODR = ODR100Hz;
	Bandwidth mBW = BWLow;
	FullScale mFS = FS250;

	float GetSensitivityCorrection() const;
};
