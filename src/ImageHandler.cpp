#include "ImageHandler.h"

// Constructor
ImageHandler::ImageHandler(ros::NodeHandle* _nh)
: nh(_nh)
{
	// nh = new ros::NodeHandle();
	it = new image_transport::ImageTransport(*nh);
	// sub = it->subscribe("usb_cam/image_raw", 1, &ImageHandler::imageCallback, this);
	sub = nh->subscribe("/blobs", 1, &ImageHandler::blobCallback, this);

}

// Destructor
ImageHandler::~ImageHandler()
{
	delete it;
}

void ImageHandler::blobCallback(const cmvision::Blobs::ConstPtr& msg)
{
	ROS_INFO("Received a blob");
	
	/* Loop through blobs */
	for (int i=0; i < msg->blob_count; ++i)
	{
		const cmvision::Blob& b = msg->blobs[i];

		/* Handle blobs with the label 'Lint' attached */
		if (b.name.compare("Lint") == 0) {
			
		}

		/* Determine if blob is close to left or right */
		int x = b.x;
			/* Have several blobs confirm this data */
			
				/* Take action and move left or right */
	}
}

