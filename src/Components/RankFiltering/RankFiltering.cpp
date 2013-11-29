/*!
 * \file
 * \brief
 * \author Mikołaj Kojdecki,,,
 */

#include <memory>
#include <string>

#include "RankFiltering.hpp"
#include "Common/Logger.hpp"

#include <boost/bind.hpp>

namespace Processors {
namespace RankFiltering {

RankFiltering::RankFiltering(const std::string & name) :
		Base::Component(name) , 
		rank("rank", 0) {
		registerProperty(rank);

}

RankFiltering::~RankFiltering() {
}

void RankFiltering::prepareInterface() {
	// Register data streams, events and event handlers HERE!
registerStream("in_img", &in_img);
registerStream("out_img", &out_img);
	// Register handlers
	h_processImage.setup(boost::bind(&RankFiltering::processImage, this));
	registerHandler("processImage", &h_processImage);
	addDependency("processImage", &in_img);

}

bool RankFiltering::onInit() {

	return true;
}

bool RankFiltering::onFinish() {
	return true;
}

bool RankFiltering::onStop() {
	return true;
}

bool RankFiltering::onStart() {
	return true;
}

void RankFiltering::processImage() {
	cv::Mat img = in_img.read().clone();
	
	if(img.channels() == 3)
	{
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
				
				img.at<cv::Vec3b>(i, j) = vec[rank].second;	
			}
	}
	else if(img.channels() == 1)
	{
		for(int i = 1; i < img.rows - 1; i++)
			for(int j = 1; j < img.cols - 1; j++)
			{
				std::vector<uchar> vec;
				for(int x = i - 1; x <= i + 1; x++)
					for(int y = j - 1; y <= j + 1; y++)
					{
						vec.push_back(img.at<uchar>(i, j));
					}
				bubbleSort(vec);
				
				img.at<uchar>(i, j) = vec[rank];	
			}
	}
	
	out_img.write(img);
}

void RankFiltering::bubbleSort(std::vector<std::pair<int, cv::Vec3b> > & vec) {
	
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

void RankFiltering::bubbleSort(std::vector<unsigned char> & vec) {
	bool unchanged = false;
	while(!unchanged)
	{
		unchanged = true;
		for(int i = 0; i < vec.size() - 1; i++)
		{
			if(vec[i] > vec[i + 1])
			{
				uchar temp = vec[i];
				vec[i] = vec[i + 1];
				vec[i + 1] = temp;
				unchanged = false;
			}
		}
	}
}

} //: namespace RankFiltering
} //: namespace Processors
