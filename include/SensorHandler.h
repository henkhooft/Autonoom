#ifndef SENSORHANDLER_H
#define SENSORHANDLER_H

#include <list>
#include "Sensor.h"
#include "ConnectionHandler.h"

class SensorHandler
{
public:
	SensorHandler();
	~SensorHandler();
	void updateAllSensors();
private:
	std::list<Sensor*> sensors;
	ConnectionHandler& cn;
};

#endif