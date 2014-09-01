/*!
 * \file
 * \brief 
 * \author Mikolaj Kojdecki
 */

#ifndef DEMUX_HPP_
#define DEMUX_HPP_

#include "Component_Aux.hpp"
#include "Component.hpp"
#include "DataStream.hpp"
#include "Property.hpp"
#include "EventHandler2.hpp"

#include <opencv2/opencv.hpp>
#include "Types/Circles.hpp"


namespace Processors {
namespace Demux {

/*!
 * \class Demux
 * \brief Demux processor class.
 *
 * 
 */
class Demux: public Base::Component {
public:
	/*!
	 * Constructor.
	 */
	Demux(const std::string & name = "Demux");

	/*!
	 * Destructor
	 */
	virtual ~Demux();

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
	Base::DataStreamIn<Types::Circles> in_circles;

	// Output data streams
	Base::DataStreamOut<float> out_x;
	Base::DataStreamOut<float> out_y;

	// Handlers
	Base::EventHandler2 h_onNewCircle;

	// Properties

	
	// Handlers
	void onNewCircle();

};

} //: namespace Demux
} //: namespace Processors

/*
 * Register processor component.
 */
REGISTER_COMPONENT("Demux", Processors::Demux::Demux)

#endif /* DEMUX_HPP_ */
