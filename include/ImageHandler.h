#ifndef IMAGEHANDLER_H
#define IMAGEHANDLER_H

#include "ros/ros.h"
#include "image_transport/image_transport.h"
#include "sensor_msgs/Image.h"
#include "cmvision/Blobs.h"

class ImageHandler
{
public:
	ImageHandler(ros::NodeHandle* _nh);
	~ImageHandler();

private:
	ros::NodeHandle* nh;
	image_transport::ImageTransport* it;
	ros::Subscriber sub;
	void blobCallback(const cmvision::Blobs::ConstPtr& b);
};


#endif
