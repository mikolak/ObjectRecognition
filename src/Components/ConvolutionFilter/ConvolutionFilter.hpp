/*!
 * \file
 * \brief 
 * \author Mikołaj Kojdecki,,,
 */

#ifndef CONVOLUTIONFILTER_HPP_
#define CONVOLUTIONFILTER_HPP_

#include "Component_Aux.hpp"
#include "Component.hpp"
#include "DataStream.hpp"
#include "Property.hpp"
#include "EventHandler2.hpp"

#include <opencv2/opencv.hpp>


namespace Processors {
namespace ConvolutionFilter {

/*!
 * \class ConvolutionFilter
 * \brief ConvolutionFilter processor class.
 *
 * ConvolutionFilter processor.
 */
class ConvolutionFilter: public Base::Component {
public:
	/*!
	 * Constructor.
	 */
	ConvolutionFilter(const std::string & name = "ConvolutionFilter");

	/*!
	 * Destructor
	 */
	virtual ~ConvolutionFilter();

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
		Base::Property<string> type;

	
	// Handlers
	void ProcessImage();

};

} //: namespace ConvolutionFilter
} //: namespace Processors

/*
 * Register processor component.
 */
REGISTER_COMPONENT("ConvolutionFilter", Processors::ConvolutionFilter::ConvolutionFilter)

#endif /* CONVOLUTIONFILTER_HPP_ */
