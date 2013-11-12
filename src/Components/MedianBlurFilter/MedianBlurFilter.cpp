/*!
 * \file
 * \brief
 * \author Mikołaj Kojdecki,,,
 */

#include <memory>
#include <string>

#include "MedianBlurFilter.hpp"
#include "Common/Logger.hpp"

#include <boost/bind.hpp>

namespace Processors {
namespace MedianBlurFilter {

MedianBlurFilter::MedianBlurFilter(const std::string & name) :
		Base::Component(name)  {

}

MedianBlurFilter::~MedianBlurFilter() {
}

void MedianBlurFilter::prepareInterface() {
	// Register data streams, events and event handlers HERE!
registerStream("in_img", &in_img);
registerStream("out_img", &out_img);
	// Register handlers
	h_ProcessImage.setup(boost::bind(&MedianBlurFilter::ProcessImage, this));
	registerHandler("ProcessImage", &h_ProcessImage);
	addDependency("ProcessImage", &in_img);
}

bool MedianBlurFilter::onInit() {

	return true;
}

bool MedianBlurFilter::onFinish() {
	return true;
}

bool MedianBlurFilter::onStop() {
	return true;
}

bool MedianBlurFilter::onStart() {
	return true;
}

void MedianBlurFilter::ProcessImage() {
	cv::Mat img = in_img.read().clone();
	
	for(int i = 1; i < img.rows - 1; i++)
		for(int j = 1; j < img.cols - 1; j++)
		{
			std::vector<std::pair<int, cv::Vec3b> > vec;
			for(int x = i - 1; x <= i + 1; x++)
				for(int y = j - 1; y <= j + 1; y++)
				{
					int val = img.at<cv::Vec3b>(i, j)[0] + img.at<cv::Vec3b>(i, j)[1] + img.at<cv::Vec3b>(i, j)[2];
					vec.push_back(std::make_pair(val, img.at<cv::Vec3b>(i, j)));
				}
			bubbleSort(vec);
			
			img.at<cv::Vec3b>(i, j) = vec[4].second;	
		}
	
	out_img.write(img);	
}

void MedianBlurFilter::bubbleSort(std::vector<std::pair<int, cv::Vec3b> > & vec) {
	
	bool unchanged = false;
	while(!unchanged)
	{
		unchanged = true;
		for(int i = 0; i < vec.size() - 1; i++)
		{
			if(vec[i].first > vec[i + 1].first)
			{
				std::pair<int, cv::Vec3b> temp = vec[i];
				vec[i] = vec[i + 1];
				vec[i + 1] = temp;
				unchanged = false;
			}
		}
	}
}


} //: namespace MedianBlurFilter
} //: namespace Processors
