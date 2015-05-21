#include "ros/ros.h"

#include "Options.h"
#include "Movement.h"
#include "Motorcontroller.h"

/* Handlers */
#include "ImageHandler.h"
#include "ConnectionHandler.h"
#include "SensorHandler.h"

void setup()
{

}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "autonoom");
	setup();


	ros::spin();
	return 0;
}