/*!
 * \file
 * \brief
 * \author Mikołaj Kojdecki,,,
 */

#include <memory>
#include <string>

#include "Thresholding.hpp"
#include "Common/Logger.hpp"

#include <boost/bind.hpp>

namespace Processors {
namespace Thresholding {

Thresholding::Thresholding(const std::string & name) :
		Base::Component(name) , 
		threshold("threshold", 200) {
		registerProperty(threshold);

}

Thresholding::~Thresholding() {
}

void Thresholding::prepareInterface() {
	// Register data streams, events and event handlers HERE!
registerStream("in_img", &in_img);
registerStream("out_img", &out_img);
	// Register handlers
	h_processImage.setup(boost::bind(&Thresholding::processImage, this));
	registerHandler("processImage", &h_processImage);
	addDependency("processImage", &in_img);

}

bool Thresholding::onInit() {

	return true;
}

bool Thresholding::onFinish() {
	return true;
}

bool Thresholding::onStop() {
	return true;
}

bool Thresholding::onStart() {
	return true;
}

void Thresholding::processImage() {
	cv::Mat img = in_img.read();
	if(img.channels() != 1)
		cv::cvtColor(img, img, CV_BGR2GRAY);
		
	for(int i = 0; i < img.rows; i++)
		for(int j = 0; j < img.cols; j++)
		{
			uchar val = img.at<uchar>(i, j);
			if(val >= threshold)
				val = 255;
			else
				val = 0;
				
			img.at<uchar>(i, j) = val;
		}
		
	out_img.write(img);
}



} //: namespace Thresholding
} //: namespace Processors
