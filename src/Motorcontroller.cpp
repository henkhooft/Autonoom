#include "Motorcontroller.h"

// Constructor
Motorcontroller::Motorcontroller()
: con(ConnectionHandler::getInstance())
{
	
}

// Destructor
Motorcontroller::~Motorcontroller()
{

}

bool Motorcontroller::drive(Movement move)
{
	int wheel_angle = move.getWheelAngle();
	int distance = move.getDistance();

	ROS_INFO("Executing move with %d wheelangle and distance %d cm", wheel_angle, distance);

	std::string s;
	s += "400|" + wheel_angle;

	con.writeString(s);

	/* Move with a specified length */
	int cm_per_sec = 10;

	con.writeString("300|10");
	sleep(distance / cm_per_sec);
	con.writeString("300|0");
}

void Motorcontroller::stop()
{
	ROS_INFO("Motor forcefully stopped");
	con.writeString("300|0");
}