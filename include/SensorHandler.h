#ifndef SENSORHANDLER_H
#define SENSORHANDLER_H

#include <list>
#include "Sensor.h"

class SensorHandler
{
public:
	SensorHandler();
	~SensorHandler();
	void updateAllSensors();
private:
	std::list<Sensor*> sensors;
};

#endif