#include "lsm303dlhc.h"

LSM303DLHCAccelerometer::LSM303DLHCAccelerometer() :
	I2CSensorInterface(0x19)
{
}

void LSM303DLHCAccelerometer::Tick()
{

}

LSM303DLHCMagnetometer::LSM303DLHCMagnetometer() :
	I2CSensorInterface(0x1E)
{
}
