#include "SensorHandler.h"

#define MAX_SONAR_RANGE 100

// Constructor
SensorHandler::SensorHandler(std::vector<Sensor*>& _sensors, Motorcontroller& _mc, ConnectionHandler& _con)
: con(_con), sensors(_sensors), mc(_mc)
{
	
}

// Destructor
SensorHandler::~SensorHandler()
{

}

void SensorHandler::updateAllSensors()
{
	if (con.writeString("200|")) {
		sleep(1);
		ROS_DEBUG("Trying to update sonars");
	}
	else {
		ROS_ERROR("Failed to write string on serial interface");
	}
}

void SensorHandler::calculateNextMove()
{
	/* First, update all sensors */
	updateAllSensors();



	/* Then, check if any objects are detected */
	bool left, right, front, back;
	left = right = front = back = false;
	for(std::vector<Sensor*>::iterator it = sensors.begin(); it != sensors.end(); ++it) {
		Sonar* son = dynamic_cast<Sonar*>(*it);

		if (son->getLastMeasurement() <= MAX_SONAR_RANGE) {
			// Do something when in range
			switch (son->Sensor::getAddress())
			{
				case 1:			// Left sonar
					left = true;
					break;
				case 2:			// Right sonar
					right = true;
					break;
				case 3:			// Front sonar
					front = true;
					break;
				case 4:			// Rear sonar
					back = true;
					break;
				default:
					ROS_WARN("Sonar got an unknown position");
					break;
			}
		}
	}

	Movement* move = NULL;

	/* Go around the object */
	if (!front)					// Move straight
	{
		move = new Movement(90, 100);
		ROS_INFO("Gotta go straight");
	}
	else if (front && !left) 	// Dodge to left
	{
		move = new Movement(70, 100);
		ROS_INFO("Dodging to the left");
	}
	else if (front && !right)	// Dodge to right
	{
		move = new Movement(110, 100);	
		ROS_INFO("Dodging to the right");
	}
	else						// Cant see for shit, move backwards
	{
		move = new Movement(90, 80);
		ROS_INFO("Stopping for obstacle");
	}


	if (back)
	{
		ROS_WARN("TEGENSTANDER GEDETECTEERD!");
	}


	if (move != NULL) {
		mc.steer(*move);
		mc.drive(*move);
	}
	else {

	}
}
