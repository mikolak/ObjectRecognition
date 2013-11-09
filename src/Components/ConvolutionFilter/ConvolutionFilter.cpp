/*!
 * \file
 * \brief
 * \author Mikołaj Kojdecki,,,
 */

#include <memory>
#include <string>

#include "ConvolutionFilter.hpp"
#include "Common/Logger.hpp"

#include <boost/bind.hpp>

namespace Processors {
namespace ConvolutionFilter {

ConvolutionFilter::ConvolutionFilter(const std::string & name) :
		Base::Component(name) , 
		type("type", string("edge_detection")) {
		registerProperty(type);

}

ConvolutionFilter::~ConvolutionFilter() {
}

void ConvolutionFilter::prepareInterface() {
	// Register data streams, events and event handlers HERE!
registerStream("in_img", &in_img);
registerStream("out_img", &out_img);
	// Register handlers
	h_ProcessImage.setup(boost::bind(&ConvolutionFilter::ProcessImage, this));
	registerHandler("ProcessImage", &h_ProcessImage);
	addDependency("ProcessImage", &in_img);

}

bool ConvolutionFilter::onInit() {

	return true;
}

bool ConvolutionFilter::onFinish() {
	return true;
}

bool ConvolutionFilter::onStop() {
	return true;
}

bool ConvolutionFilter::onStart() {
	return true;
}

void ConvolutionFilter::ProcessImage() {
	cv::Mat orig_img;
	cv::cvtColor(in_img.read(), orig_img, CV_BGR2GRAY);
	cv::Mat img = orig_img.clone();
	//cvtColor(img, img, CV_BGR2GRAY);
	//orig_img = img.clone();
	int edge_det_mask[]= {-1, -1, -1, -1, 8, -1, -1, -1, -1};
	
	//cout << img.channels() << " " << img.depth() << endl;
	for(int i = 1; i < img.rows - 1; i++)
		for(int j = 1; j < img.cols - 1; j++)
		{
			//cout << img.at<uchar>(i, j) << endl;
			int val = edge_det_mask[0] * orig_img.at<uchar>(i - 1, j - 1)
					+ edge_det_mask[1] * orig_img.at<uchar>(i - 1, j)
					+ edge_det_mask[2] * orig_img.at<uchar>(i - 1, j + 1)
					+ edge_det_mask[3] * orig_img.at<uchar>(i, j - 1)
					+ edge_det_mask[4] * orig_img.at<uchar>(i, j)
					+ edge_det_mask[5] * orig_img.at<uchar>(i, j + 1)
					+ edge_det_mask[6] * orig_img.at<uchar>(i + 1, j - 1)
					+ edge_det_mask[7] * orig_img.at<uchar>(i + 1, j)
					+ edge_det_mask[8] * orig_img.at<uchar>(i + 1, j + 1);
			
			if(val > 255) val = 255;
			if(val < 0) val = 0;		
			img.at<uchar>(i, j) = val;
		}
	
	out_img.write(img);
}



} //: namespace ConvolutionFilter
} //: namespace Processors
