#include "MessageHandler.h"

// Constructor
MessageHandler::MessageHandler(ros::NodeHandle* _nh, Options* _options)
: nh(_nh), options(_options)
{
	ros::Subscriber sub = nh->subscribe("carrequest", 1000, &MessageHandler::requestCallback, this);
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


	ROS_DEBUG("Received a new car request");

	if (msg.start != current_start)
	{
		// Start the race
		ROS_DEBUG("The car is starting/stopping");
	}

	if (msg.new_max_speed != current_max_speed)
	{
		// Write new max speed
		ROS_DEBUG("Maximum speed is changed to %ld", (long int)msg.new_max_speed);
	}

	if (msg.new_max_range != current_max_range)
	{
		// Write new maximum sonar range
		ROS_DEBUG("Maximum sonar range is changed to %ld", (long int)msg.new_max_range);
	}
}