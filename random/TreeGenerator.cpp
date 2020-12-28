#include "TreeGenerator.h"
#include <iterator>
#include <opencv2/imgproc.hpp>

void TreeGenerator::initialize(int w, int h)
{
	this->universeData = cv::Mat::zeros(w, h, CV_8UC3);
	TreeSeed initialSeed;
	initialSeed.start = cv::Point2i(w / 2, h - 10);
	initialSeed.length = 20;
	initialSeed.angle = 45;

	std::vector<TreeSeed> initialSeeds;
	initialSeeds.push_back(initialSeed);

	seeds.push_back(initialSeeds);
	iteration = 0;
}


cv::Mat TreeGenerator::getStep()
{
	cv::Scalar colorLine(0, 255, 0);
	std::vector<TreeSeed> newSeeds;
	for (TreeSeed& seed : seeds[iteration])
	{
		std::vector<TreeSeed> newItems = seed.getChildren();
		for (TreeSeed& item : newItems)
		{
			cv::line(universeData, seed.start, item.start, colorLine);
			item.length--;
			if (item.length <= 0)
				item.length = 2;
			newSeeds.push_back(item);
		}
	}

	seeds.push_back(newSeeds);
	
	iteration++;
	return universeData;
}
