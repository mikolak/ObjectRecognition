/*!
 * \file
 * \brief
 * \author Mikolaj Kojdecki
 */

#include <memory>
#include <string>

#include "DrawDetectedCircles.hpp"
#include "Common/Logger.hpp"

#include <boost/bind.hpp>

namespace Processors {
namespace DrawDetectedCircles {

DrawDetectedCircles::DrawDetectedCircles(const std::string & name) :
		Base::Component(name)  {

}

DrawDetectedCircles::~DrawDetectedCircles() {
}

void DrawDetectedCircles::prepareInterface() {
	// Register data streams, events and event handlers HERE!
	registerStream("in_img", &in_img);
	registerStream("in_circles", &in_circles);
	registerStream("out_img", &out_img);
	// Register handlers
	h_onNewImage.setup(boost::bind(&DrawDetectedCircles::onNewImage, this));
	registerHandler("onNewImage", &h_onNewImage);
	addDependency("onNewImage", &in_circles);
	addDependency("onNewImage", &in_img);

}

bool DrawDetectedCircles::onInit() {

	return true;
}

bool DrawDetectedCircles::onFinish() {
	return true;
}

bool DrawDetectedCircles::onStop() {
	return true;
}

bool DrawDetectedCircles::onStart() {
	return true;
}

void DrawDetectedCircles::onNewImage() {
	Types::Circles circles = Types::Circles(in_circles.read());
	cv::Mat img = in_img.read().clone();
	
	circles.draw(img, 240, 0, 0);
	
	out_img.write(img);
}



} //: namespace DrawDetectedCircles
} //: namespace Processors
