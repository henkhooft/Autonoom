#include "ros/ros.h"
#include <vector>

#include "Options.h"
#include "Movement.h"
#include "Motorcontroller.h"
#include "Sensor.h"

/* Handlers */
#include "ImageHandler.h"
#include "ConnectionHandler.h"
#include "SensorHandler.h"
#include "MessageHandler.h"

int main(int argc, char **argv)
{
	ros::init(argc, argv, "autonoom");

	/* Vector for containing sensors */
	std::vector<Sensor*> sensors;

	/* Fill vector with sensors (HARDCODED) */

	Options* options = new Options();

	ros::NodeHandle* nh = new ros::NodeHandle();
	MessageHandler mh(nh, options);
	ImageHandler ih(nh);

	/* Setup connection handler */
	ConnectionHandler c = ConnectionHandler::getInstance();
	c.addSensors(sensors);

	SensorHandler sh(sensors);
	Motorcontroller mc;
	c.start();

	sleep(3);

	ROS_INFO("Car node initialized");

	sleep(5);

	ROS_INFO("Executing test case...");

	sleep(5);

	/* Test case */
	Movement move(30, 30); // 30 degree for 30 cm forward
	mc.drive(move);

	ROS_INFO("Finished test case");

	ros::spin();
	return 0;
}