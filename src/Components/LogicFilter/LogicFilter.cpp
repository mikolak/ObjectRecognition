/*!
 * \file
 * \brief
 * \author Mikołaj Kojdecki,,,
 */

#include <memory>
#include <string>

#include "LogicFilter.hpp"
#include "Common/Logger.hpp"

#include <boost/bind.hpp>

namespace Processors {
namespace LogicFilter {

LogicFilter::LogicFilter(const std::string & name) :
		Base::Component(name) , 
		upper_left("upper_left", false), 
		upper_center("upper_center", false), 
		upper_right("upper_right", false), 
		left("left", false), 
		center("center", true), 
		right("right", false), 
		lower_left("lower_left", false), 
		lower_center("lower_center", false), 
		lower_right("lower_right", false) {
		registerProperty(upper_left);
		registerProperty(upper_center);
		registerProperty(upper_right);
		registerProperty(left);
		registerProperty(center);
		registerProperty(right);
		registerProperty(lower_left);
		registerProperty(lower_center);
		registerProperty(lower_right);

}

LogicFilter::~LogicFilter() {
}

void LogicFilter::prepareInterface() {
	// Register data streams, events and event handlers HERE!
registerStream("in_img", &in_img);
registerStream("out_img", &out_img);
	// Register handlers
	h_processImage.setup(boost::bind(&LogicFilter::processImage, this));
	registerHandler("processImage", &h_processImage);
	addDependency("processImage", &in_img);

}

bool LogicFilter::onInit() {

	return true;
}

bool LogicFilter::onFinish() {
	return true;
}

bool LogicFilter::onStop() {
	return true;
}

bool LogicFilter::onStart() {
	return true;
}

void LogicFilter::processImage() {
}



} //: namespace LogicFilter
} //: namespace Processors
