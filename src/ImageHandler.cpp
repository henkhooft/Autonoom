#include "ImageHandler.h"

// Constructor
ImageHandler::ImageHandler()
{
	nh = new ros::NodeHandle();
	it = new image_transport::ImageTransport(nh);
	sub = it->subscribe("camera/image", 1, imageCallback);
}

// Destructor
ImageHandler::~ImageHandler()
{
	delete nh;
	delete it;
	delete sub;
}

/**
 * @brief Callback after a new image has been received.
 * @details [long description]
 * 
 * @param msg Pointer to the image object.
 */
void ImageHandler::imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
	ROS_INFO("Image message received");
}

/**
 * @brief Processes an image.
 * @details [long description]
 */
void ImageHandler::process()
{

}