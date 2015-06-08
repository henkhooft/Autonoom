#include "ros/ros.h"

#include "Options.h"
#include "Movement.h"
#include "Motorcontroller.h"

/* Handlers */
#include "ImageHandler.h"
#include "ConnectionHandler.h"
#include "SensorHandler.h"
#include "MessageHandler.h"


void setup()
{

}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "autonoom");
	setup();

	Options* options = new Options();

	ros::NodeHandle* nh = new ros::NodeHandle();
	MessageHandler mh(nh, options);
	ImageHandler ih(nh);


	ROS_INFO("Car node initialized");
	ros::spin();
	return 0;
}