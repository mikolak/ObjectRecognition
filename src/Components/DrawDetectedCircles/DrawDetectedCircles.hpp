/*!
 * \file
 * \brief 
 * \author Mikolaj Kojdecki
 */

#ifndef DRAWDETECTEDCIRCLES_HPP_
#define DRAWDETECTEDCIRCLES_HPP_

#include "Component_Aux.hpp"
#include "Component.hpp"
#include "DataStream.hpp"
#include "Property.hpp"
#include "EventHandler2.hpp"
#include "Types/Circles/Circles.hpp"

#include <opencv2/opencv.hpp>


namespace Processors {
namespace DrawDetectedCircles {

/*!
 * \class DrawDetectedCircles
 * \brief DrawDetectedCircles processor class.
 *
 * 
 */
class DrawDetectedCircles: public Base::Component {
public:
	/*!
	 * Constructor.
	 */
	DrawDetectedCircles(const std::string & name = "DrawDetectedCircles");

	/*!
	 * Destructor
	 */
	virtual ~DrawDetectedCircles();

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
	Base::DataStreamIn<Types::Circles> in_circles;

	// Output data streams
	Base::DataStreamOut<cv::Mat> out_img;

	// Handlers
	Base::EventHandler2 h_onNewImage;

	// Properties

	
	// Handlers
	void onNewImage();

};

} //: namespace DrawDetectedCircles
} //: namespace Processors

/*
 * Register processor component.
 */
REGISTER_COMPONENT("DrawDetectedCircles", Processors::DrawDetectedCircles::DrawDetectedCircles)

#endif /* DRAWDETECTEDCIRCLES_HPP_ */
