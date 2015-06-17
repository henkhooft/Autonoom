#include "MessageHandler.h"

// Constructor
MessageHandler::MessageHandler(ros::NodeHandle* _nh, Options* _options)
: nh(_nh), options(_options)
{
	sub = nh->subscribe("carrequest", 1, &MessageHandler::requestCallback, this);
	pub_status = nh->advertise<autonoom::CarResponse>("carresponse", 1000);
}

// Destructor
MessageHandler::~MessageHandler()
{
	
}

// Callback for handling a new request from the control node
void MessageHandler::requestCallback(const autonoom::CarRequest& msg)
{
	// Get current status
	int current_max_speed, current_max_range;
	bool current_start;
	if (options != NULL)
	{
		current_start = options->getIsDriving();
		current_max_speed = options->getMaxSpeed();
		current_max_range = options->getMaxRange();
	}
	else
	{
		ROS_ERROR("Options was not initialized");
	}


	ROS_INFO("Received a new car request");

	if (msg.start != current_start)
	{
		// Start the race
		ROS_INFO("The car is starting/stopping");
	}

	if (msg.new_max_speed != current_max_speed)
	{
		// Write new max speed
		ROS_INFO("Maximum speed is changed to %ld", (long int)msg.new_max_speed);
	}

	if (msg.new_max_range != current_max_range)
	{
		// Write new maximum sonar range
		ROS_INFO("Maximum sonar range is changed to %ld", (long int)msg.new_max_range);
	}
}