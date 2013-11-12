/*!
 * \file
 * \brief 
 * \author Mikołaj Kojdecki,,,
 */

#ifndef MEDIANBLURFILTER_HPP_
#define MEDIANBLURFILTER_HPP_

#include "Component_Aux.hpp"
#include "Component.hpp"
#include "DataStream.hpp"
#include "Property.hpp"
#include "EventHandler2.hpp"

#include <opencv2/opencv.hpp>


namespace Processors {
namespace MedianBlurFilter {

/*!
 * \class MedianBlurFilter
 * \brief MedianBlurFilter processor class.
 *
 * MedianBlurFilter processor.
 */
class MedianBlurFilter: public Base::Component {
public:
	/*!
	 * Constructor.
	 */
	MedianBlurFilter(const std::string & name = "MedianBlurFilter");

	/*!
	 * Destructor
	 */
	virtual ~MedianBlurFilter();

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

	
	// Handlers
	void ProcessImage();
	
	
private:
	void bubbleSort(std::vector<std::pair<int, cv::Vec3b> > &);
};

} //: namespace MedianBlurFilter
} //: namespace Processors

/*
 * Register processor component.
 */
REGISTER_COMPONENT("MedianBlurFilter", Processors::MedianBlurFilter::MedianBlurFilter)

#endif /* MEDIANBLURFILTER_HPP_ */
