#ifndef SENSORHANDLER_H
#define SENSORHANDLER_H

#include <vector>
#include "Sensor.h"
#include "Sonar.h"
#include "ConnectionHandler.h"
#include "Motorcontroller.h"
#include "Movement.h"

class SensorHandler
{
public:
	SensorHandler(std::vector<Sensor*> _sensors, Motorcontroller _mc);
	~SensorHandler();
	void updateAllSensors();
private:
	std::vector<Sensor*> sensors;
	Motorcontroller mc;
	ConnectionHandler& cn;
	void calculateNextMove();
};

#endif