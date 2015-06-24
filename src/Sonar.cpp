#include "Sonar.h"

// Constructor
Sonar::Sonar(int _address)
	: Sensor(_address)
{

}

// Destructor
Sonar::~Sonar()
{

}

int Sonar::getLastMeasurement()
{
	return lastMeasurementInCm;
}
