#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include "ros/ros.h"
#include "autonoom/CarRequest.h"
#include "autonoom/CarResponse.h"
#include "Options.h"

// Class for handling messages
class MessageHandler
{
public:
	MessageHandler(ros::NodeHandle* _nh, Options* _options);
	~MessageHandler();
private:
	void requestCallback(const autonoom::CarRequest& msg);
	Options* options;

	// ROS attributes
	ros::NodeHandle* nh;
	ros::Publisher pub_status;
};

#endif