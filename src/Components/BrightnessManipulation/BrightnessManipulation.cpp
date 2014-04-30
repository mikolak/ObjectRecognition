/*!
 * \file
 * \brief
 * \author Mikołaj Kojdecki,,,
 */

#include <memory>
#include <string>

#include "BrightnessManipulation.hpp"
#include "Common/Logger.hpp"

#include <boost/bind.hpp>

namespace Processors {
namespace BrightnessManipulation {

BrightnessManipulation::BrightnessManipulation(const std::string & name) :
		Base::Component(name) , 
		gain("gain", 20) {
		registerProperty(gain);

}

BrightnessManipulation::~BrightnessManipulation() {
}

void BrightnessManipulation::prepareInterface() {
	// Register data streams, events and event handlers HERE!
registerStream("in_img", &in_img);
registerStream("out_img", &out_img);
	// Register handlers
	h_onImage.setup(boost::bind(&BrightnessManipulation::onImage, this));
	registerHandler("onImage", &h_onImage);
	addDependency("onImage", &in_img);

}

bool BrightnessManipulation::onInit() {

	return true;
}

bool BrightnessManipulation::onFinish() {
	return true;
}

bool BrightnessManipulation::onStop() {
	return true;
}

bool BrightnessManipulation::onStart() {
	return true;
}

void BrightnessManipulation::onImage() {
	cv::Mat img = in_img.read().clone();
	
	//cout << img.depth() << " chan " << img.channels() << endl;
	for(int i = 0; i < img.rows; i++)
		for(int j = 0; j < img.cols; j++)
		{
			int val1 = (int) (img.at<cv::Vec3b>(i, j)[0] + gain);
			int val2 = (int) (img.at<cv::Vec3b>(i, j)[1] + gain);
			int val3 = (int) (img.at<cv::Vec3b>(i, j)[2] + gain);
			
			if(val1 > 255) val1 = 255;
			if(val2 > 255) val2 = 255;
			if(val3 > 255) val3 = 255;

			img.at<cv::Vec3b>(i, j)[0] = val1;
			img.at<cv::Vec3b>(i, j)[1] = val2;
			img.at<cv::Vec3b>(i, j)[2] = val3;
		}
		
	out_img.write(img);
}



} //: namespace BrightnessManipulation
} //: namespace Processors
