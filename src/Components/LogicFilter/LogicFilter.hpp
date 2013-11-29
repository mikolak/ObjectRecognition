/*!
 * \file
 * \brief 
 * \author Mikołaj Kojdecki,,,
 */

#ifndef LOGICFILTER_HPP_
#define LOGICFILTER_HPP_

#include "Component_Aux.hpp"
#include "Component.hpp"
#include "DataStream.hpp"
#include "Property.hpp"
#include "EventHandler2.hpp"

#include <opencv2/opencv.hpp>


namespace Processors {
namespace LogicFilter {

/*!
 * \class LogicFilter
 * \brief LogicFilter processor class.
 *
 * LogicFilter processor.
 */
class LogicFilter: public Base::Component {
public:
	/*!
	 * Constructor.
	 */
	LogicFilter(const std::string & name = "LogicFilter");

	/*!
	 * Destructor
	 */
	virtual ~LogicFilter();

	/*!
	 * Prepare components interface (register streams and handlers).
	 * At this point, all properties are already initialized and loaded to 
	 * values set in config file.
	 */
	void prepareInterface();

protected:

	/*!
	 * Connects source to given device.
	 */
	bool onInit();

	/*!
	 * Disconnect source from device, closes streams, etc.
	 */
	bool onFinish();

	/*!
	 * Start component
	 */
	bool onStart();

	/*!
	 * Stop component
	 */
	bool onStop();


// Input data streams

		Base::DataStreamIn<cv::Mat> in_img;

// Output data streams

		Base::DataStreamOut<cv::Mat> out_img;
	// Handlers
	Base::EventHandler2 h_processImage;
		Base::Property<bool> upper_left;
		Base::Property<bool> upper_center;
		Base::Property<bool> upper_right;
		Base::Property<bool> left;
		Base::Property<bool> center;
		Base::Property<bool> right;
		Base::Property<bool> lower_left;
		Base::Property<bool> lower_center;
		Base::Property<bool> lower_right;

	
	// Handlers
	void processImage();

};

} //: namespace LogicFilter
} //: namespace Processors

/*
 * Register processor component.
 */
REGISTER_COMPONENT("LogicFilter", Processors::LogicFilter::LogicFilter)

#endif /* LOGICFILTER_HPP_ */
