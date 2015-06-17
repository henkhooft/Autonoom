#include "SensorHandler.h"

// Constructor
SensorHandler::SensorHandler(std::vector<Sensor*> _sensors)
: cn(ConnectionHandler::getInstance()), sensors(_sensors)
{
	
}

// Destructor
SensorHandler::~SensorHandler()
{

}

void SensorHandler::updateAllSensors()
{
	if (cn.writeString("200")) {
		ROS_DEBUG("Trying to update sonars");
	}
	else {
		ROS_ERROR("Failed to write string on serial interface");
	}
}