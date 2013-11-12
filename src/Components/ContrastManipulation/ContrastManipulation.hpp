/*!
 * \file
 * \brief 
 * \author Mikołaj Kojdecki,,,
 */

#ifndef CONTRASTMANIPULATION_HPP_
#define CONTRASTMANIPULATION_HPP_

#include "Component_Aux.hpp"
#include "Component.hpp"
#include "DataStream.hpp"
#include "Property.hpp"
#include "EventHandler2.hpp"

#include <opencv2/opencv.hpp>


namespace Processors {
namespace ContrastManipulation {

/*!
 * \class ContrastManipulation
 * \brief ContrastManipulation processor class.
 *
 * ContrastManipulation processor.
 */
class ContrastManipulation: public Base::Component {
public:
	/*!
	 * Constructor.
	 */
	ContrastManipulation(const std::string & name = "ContrastManipulation");

	/*!
	 * Destructor
	 */
	virtual ~ContrastManipulation();

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
	Base::EventHandler2 h_ProcessImage;
		Base::Property<float> contrast_gain;

	
	// Handlers
	void ProcessImage();

};

} //: namespace ContrastManipulation
} //: namespace Processors

/*
 * Register processor component.
 */
REGISTER_COMPONENT("ContrastManipulation", Processors::ContrastManipulation::ContrastManipulation)

#endif /* CONTRASTMANIPULATION_HPP_ */
