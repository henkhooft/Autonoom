#include "Motorcontroller.h"

bool Motorcontroller::TURBO = false;

// Constructor
Motorcontroller::Motorcontroller(ConnectionHandler& _con)
: con(_con) 
{

}

// Destructor
Motorcontroller::~Motorcontroller()
{

}

void Motorcontroller::steer(Movement move)
{
	int wheel_angle = move.getWheelAngle();
	std::ostringstream ss;
	ss << "400|" << wheel_angle;

	ROS_INFO("Executing move with angle %d", wheel_angle-90); 
	con.writeString(ss.str());
}

bool Motorcontroller::drive(Movement move)
{
	int distance = move.getDistance();

	ROS_INFO("Executing move with speed %d", distance-90); 

	if (TURBO)
	{
		for (int i=0; i<20; i++)
		{
			ROS_FATAL("GOING FULL TURBO MODE!!!!!!");
		}
		if (distance > 90)
		{
			distance = 120;
		}
		else if (distance < 90)
		{
			distance = 60;
		}		
	}

	// sleep(1);

	std::ostringstream sd;
	sd << "300|" << distance;
	con.writeString(sd.str());
}

void Motorcontroller::stop()
{
	ROS_INFO("Motor forcefully stopped");
	con.writeString("300|90");
}
