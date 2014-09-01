/*!
 * \file
 * \brief
 * \author Mikolaj Kojdecki
 */

#include <memory>
#include <string>

#include "Demux.hpp"
#include "Common/Logger.hpp"

#include <boost/bind.hpp>

namespace Processors {
namespace Demux {

Demux::Demux(const std::string & name) :
		Base::Component(name)  {

}

Demux::~Demux() {
}

void Demux::prepareInterface() {
	// Register data streams, events and event handlers HERE!
	registerStream("in_circles", &in_circles);
	registerStream("out_x", &out_x);
	registerStream("out_y", &out_y);
	// Register handlers
	h_onNewCircle.setup(boost::bind(&Demux::onNewCircle, this));
	registerHandler("onNewCircle", &h_onNewCircle);
	addDependency("onNewCircle", &in_circles);

}

bool Demux::onInit() {

	return true;
}

bool Demux::onFinish() {
	return true;
}

bool Demux::onStop() {
	return true;
}

bool Demux::onStart() {
	return true;
}

void Demux::onNewCircle() {
	Types::Circles circles = Types::Circles(in_circles.read());
	
	if(!circles.circles.empty())
	{
		std::cout << "NIEPUSTE============================" << endl;
		int index = 0;
		for(int i = 0; i < circles.circles.size(); i++)
		{
			if(circles.circles[i][2] > circles.circles[index][2])
				index = i;
		}
			
		out_x.write(circles.circles[index][0]);
		out_y.write(circles.circles[index][1]);
	}
	else
		std::cout << "PUSTE~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
}



} //: namespace Demux
} //: namespace Processors
