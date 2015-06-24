#ifndef SONAR_H
#define SONAR_H

#include "Sensor.h"

class Sonar : public Sensor
{
public:
	Sonar(int _address);
	~Sonar();
	int getLastMeasurement();
	int setMeasurement(int value) { lastMeasurementInCm = value; }
private:
	int lastMeasurementInCm;
};

#endif
