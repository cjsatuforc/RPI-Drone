#pragma once

class OrientationInterface
{
public:

	virtual ~OrientationInterface() {};
	virtual void Initialize() = 0;
	virtual void Tick() = 0;
	virtual float GetRoll() = 0;
	virtual float GetPitch() = 0;
	virtual float GetYaw() = 0;
};
