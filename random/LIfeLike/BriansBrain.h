#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2\core\base.hpp>
#include "Seed.h"

class BriansBrain : public Seed
{
public:
	void initialize(int w, int h, std::string data);
	cv::Mat getStep();
};

