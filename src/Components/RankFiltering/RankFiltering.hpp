/*!
 * \file
 * \brief 
 * \author Mikołaj Kojdecki,,,
 */

#ifndef RANKFILTERING_HPP_
#define RANKFILTERING_HPP_

#include "Component_Aux.hpp"
#include "Component.hpp"
#include "DataStream.hpp"
#include "Property.hpp"
#include "EventHandler2.hpp"

#include <opencv2/opencv.hpp>


namespace Processors {
namespace RankFiltering {

/*!
 * \class RankFiltering
 * \brief RankFiltering processor class.
 *
 * RankFiltering processor.
 */
class RankFiltering: public Base::Component {
public:
	/*!
	 * Constructor.
	 */
	RankFiltering(const std::string & name = "RankFiltering");

	/*!
	 * Destructor
	 */
	virtual ~RankFiltering();

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
		Base::Property<int> rank;

	
	// Handlers
	void processImage();
	
private:
	void bubbleSort(std::vector<std::pair<int, cv::Vec3b> > &);
	void bubbleSort(std::vector<unsigned char> &);

};

} //: namespace RankFiltering
} //: namespace Processors

/*
 * Register processor component.
 */
REGISTER_COMPONENT("RankFiltering", Processors::RankFiltering::RankFiltering)

#endif /* RANKFILTERING_HPP_ */
