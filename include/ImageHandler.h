#ifndef IMAGEHANDLER_H
#define IMAGEHANDLER_H

#include "ros/ros.h"
#include "image_transport/image_transport.h"
#include "sensor_msgs/Image.h"
#include "ImageProcessor.h"

class ImageHandler
{
public:
	ImageHandler();
	~ImageHandler();
	void imageCallback(const sensor_msgs::ImageConstPtr& msg);
	void process();
private:
	ros::NodeHandle* nh;
	image_transport::ImageTransport* it;
	image_transport::Subscriber* sub;
	ImageProcessor processor;
};


#endif