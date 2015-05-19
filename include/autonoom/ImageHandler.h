#ifndef IMAGEHANDLER_H
#define IMAGEHANDLER_H

#include "ros/ros.h"
#include "ros/image_transport.h"
#include "ros/sensor_msgs.h"
#include "ImageProcessor.h"

class ImageHandler
{
public:
	ImageHandler();
	~ImageHandler();
	void imageCallback(const sensor_msgs::ImageCOnstPtr& msg);
	void process();
private:
	ros::NodeHandle nh;
	image_transport::ImageTransport it;
	image_transport::Subscriber sub;
	ImageProcessor processor;
};


#endif