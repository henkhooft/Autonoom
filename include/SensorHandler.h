#ifndef SENSORHANDLER_H
#define SENSORHANDLER_H

#include <vector>
#include "Sensor.h"
#include "ConnectionHandler.h"

class SensorHandler
{
public:
	SensorHandler(std::vector<Sensor*> _sensors);
	~SensorHandler();
	void updateAllSensors();
private:
	std::vector<Sensor*> sensors;
	ConnectionHandler& cn;
};

#endif