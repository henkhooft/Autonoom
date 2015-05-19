#ifndef SONAR_H
#define SONAR_H

#include "Sensor.h"

class Sonar : Sensor
{
public:
	Sonar(int _address);
	~Sonar();
private:
	int lastMeasurementInCm();
};

#endif