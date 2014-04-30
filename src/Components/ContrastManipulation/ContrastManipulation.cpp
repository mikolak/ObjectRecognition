/*!
 * \file
 * \brief
 * \author Mikołaj Kojdecki,,,
 */

#include <memory>
#include <string>

#include "ContrastManipulation.hpp"
#include "Common/Logger.hpp"

#include <boost/bind.hpp>

namespace Processors {
namespace ContrastManipulation {

ContrastManipulation::ContrastManipulation(const std::string & name) :
		Base::Component(name) , 
		contrast_gain("contrast_gain", 2.5) {
		registerProperty(contrast_gain);

}

ContrastManipulation::~ContrastManipulation() {
}

void ContrastManipulation::prepareInterface() {
	// Register data streams, events and event handlers HERE!
registerStream("in_img", &in_img);
registerStream("out_img", &out_img);
	// Register handlers
	h_ProcessImage.setup(boost::bind(&ContrastManipulation::ProcessImage, this));
	registerHandler("ProcessImage", &h_ProcessImage);
	addDependency("ProcessImage", &in_img);

}

bool ContrastManipulation::onInit() {

	return true;
}

bool ContrastManipulation::onFinish() {
	return true;
}

bool ContrastManipulation::onStop() {
	return true;
}

bool ContrastManipulation::onStart() {
	return true;
}

void ContrastManipulation::ProcessImage() {
	cv::Mat img = in_img.read();
	img = img.clone();
	
	//cout << img.depth() << " chan " << img.channels() << endl;
	for(int i = 0; i < img.rows; i++)
		for(int j = 0; j < img.cols; j++)
		{
			int blue, green, red;
			blue = img.at<cv::Vec3b>(i, j)[0] * contrast_gain;
			green = img.at<cv::Vec3b>(i, j)[1] * contrast_gain;
			red = img.at<cv::Vec3b>(i, j)[2] * contrast_gain;
			
			if(blue > 255) blue = 255;
			if(green > 255) green = 255;
			if(red > 255) red = 255;
			
			img.at<cv::Vec3b>(i, j)[0] = blue;
			img.at<cv::Vec3b>(i, j)[1] = green;
			img.at<cv::Vec3b>(i, j)[2] = red; 
		}
		
	out_img.write(img);
}



} //: namespace ContrastManipulation
} //: namespace Processors
