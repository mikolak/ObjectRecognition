/*!
 * \file
 * \brief 
 * \author Mikołaj Kojdecki,,,
 */

#ifndef THRESHOLDING_HPP_
#define THRESHOLDING_HPP_

#include "Component_Aux.hpp"
#include "Component.hpp"
#include "DataStream.hpp"
#include "Property.hpp"
#include "EventHandler2.hpp"

#include <opencv2/opencv.hpp>


namespace Processors {
namespace Thresholding {

/*!
 * \class Thresholding
 * \brief Thresholding processor class.
 *
 * Thresholding processor.
 */
class Thresholding: public Base::Component {
public:
	/*!
	 * Constructor.
	 */
	Thresholding(const std::string & name = "Thresholding");

	/*!
	 * Destructor
	 */
	virtual ~Thresholding();

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
		Base::Property<int> threshold;

	
	// Handlers
	void processImage();

};

} //: namespace Thresholding
} //: namespace Processors

/*
 * Register processor component.
 */
REGISTER_COMPONENT("Thresholding", Processors::Thresholding::Thresholding)

#endif /* THRESHOLDING_HPP_ */
