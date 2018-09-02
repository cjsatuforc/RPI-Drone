#pragma once

#include "OrientationInterface.h"

class MagnetoOrientation : public OrientationInterface
{
public:
	MagnetoOrientation();
	virtual ~MagnetoOrientation();

	virtual void Initialize() override;
	virtual void Tick() override;
	virtual float GetRoll() override;
	virtual float GetPitch() override;
	virtual float GetYaw() override;
};

