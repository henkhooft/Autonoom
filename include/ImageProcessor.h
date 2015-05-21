#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include "sensor_msgs/Image.h"

class ImageProcessor
{
public:
	ImageProcessor();
	~ImageProcessor();
	void process(const sensor_msgs::ImageConstPtr& msg);
};

#endif