/*!
 * \file
 * \brief 
 * \author Mikołaj Kojdecki,,,
 */

#ifndef BRIGHTNESSMANIPULATION_HPP_
#define BRIGHTNESSMANIPULATION_HPP_

#include "Component_Aux.hpp"
#include "Component.hpp"
#include "DataStream.hpp"
#include "Property.hpp"
#include "EventHandler2.hpp"

#include <opencv2/opencv.hpp>


namespace Processors {
namespace BrightnessManipulation {

/*!
 * \class BrightnessManipulation
 * \brief BrightnessManipulation processor class.
 *
 * BrightnessManipulation processor.
 */
class BrightnessManipulation: public Base::Component {
public:
	/*!
	 * Constructor.
	 */
	BrightnessManipulation(const std::string & name = "BrightnessManipulation");

	/*!
	 * Destructor
	 */
	virtual ~BrightnessManipulation();

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
	Base::EventHandler2 h_onImage;
		Base::Property<int> gain;

	
	// Handlers
	void onImage();

};

} //: namespace BrightnessManipulation
} //: namespace Processors

/*
 * Register processor component.
 */
REGISTER_COMPONENT("BrightnessManipulation", Processors::BrightnessManipulation::BrightnessManipulation)

#endif /* BRIGHTNESSMANIPULATION_HPP_ */
