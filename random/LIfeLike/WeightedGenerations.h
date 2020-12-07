#pragma once
#include "Generations.h"
class WeightedGenerations : public Generations
{
public:
	void initialize(int w, int h, std::string data);
	cv::Mat getStepFilter();
	cv::Mat getStep();
};

