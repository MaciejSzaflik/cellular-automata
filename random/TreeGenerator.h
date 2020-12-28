#pragma once
#include "TreeSeed.h"
#include <opencv2/core/core.hpp>
#include <opencv2\core\base.hpp>

class TreeGenerator
{
	public:
		TreeSeed seed;
		cv::Mat universeData;
		virtual void initialize(int w, int h);
		virtual cv::Mat getStep();
	private:
		int iteration;
		std::vector<std::vector<TreeSeed>> seeds;
};

