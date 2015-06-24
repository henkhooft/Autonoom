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
	sensors.push_back(new Sonar(1));
	sensors.push_back(new Sonar(2));
	sensors.push_back(new Sonar(3));
	sensors.push_back(new Sonar(4));

	Options* options = new Options();

	ros::NodeHandle* nh = new ros::NodeHandle();
	MessageHandler mh(nh, options);
	ImageHandler ih(nh);

	/* Setup connection handler */
	ConnectionHandler c(sensors);

	Motorcontroller mc(c);
	SensorHandler sh(sensors, mc, c);
	c.start();

	sleep(3);

	ROS_INFO("Car node initialized");

	sleep(5);

	ROS_INFO("Executing test case...");
	sleep(5);

	/* Test case */
	Movement move(30, 30); // 30 degree for 30 cm forward
	mc.drive(move);
	sleep(3);
	ROS_INFO("Finished test case");
	c.writeString("200|");
	ROS_INFO("Finished sonar test");

	sh.calculateNextMove();

	ros::Rate loop_rate(10);
	while (ros::ok())
	{
		sh.calculateNextMove();
		ros::spinOnce();

		loop_rate.sleep();
	}

	ros::spin();
	return 0;
}
